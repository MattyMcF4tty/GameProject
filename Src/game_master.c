#include "game_master.h"
#include "joystick30010.h"
#include "render.h"
#include "math.h"
#include "sprites.h"
#include "hud.h"
#include "ansi.h"
#include "joystick30010.h"
#include "LCD.h"

/* ----------- Static function definitions ---------- */
static void entitySpawner(const gameConfig_t *config, gameState_t *state);
static void addAsteroid(const gameConfig_t *config, asteroid_t *asteroidArray);
static void updateAsteroids(const gameConfig_t *config, asteroid_t *asteroidArray);
static void addUfo(const gameConfig_t *config, ufo_t *ufoArray);
static void updateUfos(const gameConfig_t *config, ufo_t *ufoArray, bullet_t *bulletArray, uint8_t *lives, uint32_t *score);
static void addBullet(const gameConfig_t *config, bullet_t *bulletArray, int16_t x, int16_t y, int16_t vX, int16_t vY);
static uint8_t detectHit(const gameConfig_t *config, gameState_t *state, bullet_t *bullet, spaceship_t *ship);
static void updateBullets(const gameConfig_t *config, gameState_t *state, spaceship_t *ship, uint8_t *lives);
static void updateLCD(const gameState_t *gameState);


/* ----------- RANDOMNESS ---------- */
// Should use pin noise and should be in stm helpers
static uint32_t randomRange(uint32_t min, uint32_t max) {
    if (max < min) {
        return min;  // or swap, or assert
    }

    uint32_t span = max - min + 1;
    return min + ((uint32_t)rand() % span);
}

/* ---------- Public functions ---------- */
uint8_t initGameState(const gameConfig_t *config, gameState_t *state) {

	// We allocate the needed memory for game
    state->ufoArray = calloc(config->maxUfos, sizeof(ufo_t));
    state->asteroidArray = calloc(config->maxAsteroids, sizeof(asteroid_t));
    state->bulletArray = calloc(config->maxBullets, sizeof(bullet_t));
    state->ship = calloc(1, sizeof(spaceship_t));

    if (!state->ufoArray || !state->asteroidArray || !state->bulletArray) {
    	// Allocation failed, clean up

    	free(state->ufoArray);
		free(state->asteroidArray);
		free(state->bulletArray);
		free(state->ship);

    	return 1;
    }

    addSpaceship(state->ship,
                 (int16_t)(0 << 6),
                 (int16_t)((config->winH - SPRITE_SHIP_H) << 6));
    state->lives = 3;
    state->score = 0;
    lcdTextInit();

    return 0;
}

void updateGameState(const gameConfig_t *config, gameState_t *state) {
    // Read button state
    if (readButton(0)) {
        state->bossKeyPressed = 1;
    } else {
        state->bossKeyPressed = 0;
    }

    //Boss key mode
    if (state->bossKeyPressed && !state->bossModeActive) {
        bossKey();
        state->bossModeActive = 1;

    } else if (state->bossKeyPressed && state->bossModeActive) {
    	state->bossModeActive = 0;

    }
    // Normal gamemode
    else if (!state->bossModeActive) {
        entitySpawner(config, state);
        updateSpaceship(config, state->ship, state->bulletArray);
        updateAsteroids(config, state->asteroidArray);
        updateUfos(config, state->ufoArray, state->bulletArray, &state->lives, &state->score);
        updateBullets(config, state, state->ship, state->lives);
        updateLCD(state);
    }

    // Save button state for next frame
    state->prevBossKeyPressed = state->bossKeyPressed;
}

void updateLCD(const gameState_t *gameState)
{
    char text[32];


    memset(lcd_buffer, 0x00, sizeof(lcd_buffer)); // Clear entire LCD buffer

    snprintf(text, sizeof(text), "Lives: %u", gameState->lives);
    lcdWriteString(text, 0, 0);

    snprintf(text, sizeof(text), "Score: %lu", gameState->score);
    lcdWriteString(text, 0, 1);

    lcd_push_buffer(lcd_buffer);
}



/*------------ Local functions ---------- */
static void entitySpawner(const gameConfig_t *config, gameState_t *state) {
	uint16_t spawn = (uint16_t)randomRange(0, 1000);

	if (spawn <= 3) { // 0.3% spawn change
		addAsteroid(config, state->asteroidArray);
	}
	if (spawn <= 10) { //1.0% spawn change
		addUfo(config, state->ufoArray);
	}
}

/* ----------- ASTEROID ---------- */
static void addAsteroid(const gameConfig_t *config, asteroid_t *asteroidArray) {
	for (uint8_t i = 0; i < config->maxAsteroids; i++) {
		asteroid_t *asteroid = &asteroidArray[i];

		if (asteroid->active) continue; // Skip if index already initialized

		uint8_t randType = (uint8_t)randomRange(0, 1);

		asteroid->active = 1;
		asteroid->lives = 10;
		asteroid->x = (int16_t)randomRange(1 << 6, config->winW << 6);	// Spawn within 1 -> width
		asteroid->y = 0;
		asteroid->vX = 0;
		asteroid->vY = (int16_t)randomRange(1<<2, 1<<4); 				// speed: 1/32 -> 1/4
		asteroid->type = randType;
		asteroid->gravity = (int16_t)randomRange(1 << 4, 1 << 5);		// 1/4 -> 1/2

		break; // Stop after initialization
	}
}


static void updateAsteroids(const gameConfig_t *config, asteroid_t *asteroidArray) {
	for (uint8_t i = 0; i < config->maxAsteroids; i++) {
		asteroid_t *asteroid = &asteroidArray[i];

		if (!asteroid->active) continue; // Skip non-initialized asteroids

		int16_t oldXCell = asteroid->x >> 6;
		int16_t oldYCell = asteroid->y >> 6;

		// Detect if asteroid should be redrawn in a different cell
		asteroid->x += asteroid->vX;
		asteroid->y += asteroid->vY;
		uint8_t xMoved = oldXCell != (asteroid->x >> 6);
		uint8_t yMoved = oldYCell  != (asteroid->y >> 6);

		if ((asteroid->y >> 6) >= config->winH || asteroid->lives <= 0) { // Reached bottom or dead
			blitAsteroid(asteroid, ERASE);

			asteroid->active = 0;

			hudLoseLife();
		} else {
			if (xMoved || yMoved) {
				blitAsteroid(asteroid, ERASE);
				blitAsteroid(asteroid, DRAW);
			}
		}
	}
}


/* ----------- UFOS ---------- */
static void addUfo(const gameConfig_t *config, ufo_t *ufoArray) {
	for (uint8_t i = 0; i < config->maxUfos; i++) {
		ufo_t *ufo = &ufoArray[i];


		if (ufo->active) continue; // Skip if index already initialized

		uint8_t randType = (uint8_t)randomRange(0, 4);

		ufo->active = 1;
		ufo->lives = 3;
		ufo->x = (int16_t)randomRange(1 << 6, config->winW << 6);	// Spawn within 1 -> width
		ufo->y = 0;
		ufo->vX = 0;
		ufo->vY = (int16_t)randomRange(1<<2, 1<<3);					// speed: 1/32 -> 1/16
		ufo->type = randType;
		ufo->shotDelay = (randType + 1) << 5;						// Aggressiveness based of type

		break; // Stop after initialization

	}
}


static void updateUfos(const gameConfig_t *config, ufo_t *ufoArray, bullet_t *bulletArray, uint8_t *lives, uint32_t *score) {
	for (uint8_t i = 0; i < config->maxUfos; i++) {
		ufo_t *ufo = &ufoArray[i];


		if (!ufo->active) continue; // Skip non-initialized UFO's

		// Detect if UFO should be redrawn in a different cell
		int16_t oldXCell = ufo->x >> 6;
		int16_t oldYCell = ufo->y >> 6;
		uint8_t xMoved = oldXCell != ((ufo->x += ufo->vX) >> 6);
		uint8_t yMoved = oldYCell != ((ufo->y += ufo->vY) >> 6);

		if (ufo->lives <= 0) { // Dead
			blitUfo(ufo, ERASE);
			ufo->active = 0;
			*score += 10;
		}

		else if ((ufo->y >> 6) >= config->winH) { //Hit bottom
			blitUfo(ufo, ERASE);
			ufo->active = 0;

			if (*lives > 0){
				*lives -= 1;
			}

			hudLoseLife();

		}

	    else {
			if (xMoved || yMoved) {
				blitUfo(ufo, ERASE);
				blitUfo(ufo, DRAW);
			}
			ufo->shotDelay--;
			if (ufo->shotDelay == 0) {
				int16_t bulletX = ufo->x + (1 << 6);
				int16_t bulletY = ufo->y + (2 << 6);

				addBullet(config, bulletArray, bulletX , bulletY, 0, ufo->vY);

				ufo->shotDelay = (ufo->type + 1) << 4; // Reset shotDelay
			}
		}
	}
}


/* ----------- BULLETS ---------- */
static void addBullet(const gameConfig_t *config, bullet_t *bulletArray, int16_t x, int16_t y, int16_t vX, int16_t vY) {
    for (uint8_t i = 0; i < config->maxBullets; i++) {
        bullet_t *bullet = &bulletArray[i];

        if (bullet->active) continue; // Skip if index already initialized

        bullet->active = 1;
        bullet->x = x;
        bullet->y = y;
        bullet->vX = vX;
        bullet->vY = (vY < 0) ? -(3 << 5) : (3 << 5); // Make bullet move 1.5 cells per frame

        break;
    }
}

static void updateBullets(const gameConfig_t *config, gameState_t *state, spaceship_t *ship, uint8_t *lives) {
	for (uint8_t i = 0; i < config->maxBullets; i++) {
		bullet_t *bullet = &state->bulletArray[i];

		if (!bullet->active) continue; 			// Skip non-initialized bullets



		for (uint8_t astIndex = 0; astIndex < config->maxAsteroids; astIndex++) {
		    asteroid_t *asteroid = &state->asteroidArray[astIndex];

		    if (!asteroid->active) continue;	// Skip non-initialized asteroids

		    applyAsteroidGravity(bullet, asteroid);
		}

		// Detect if bullet should be redrawn in a new cell
		int16_t oldXCell = bullet->x >> 6;
		int16_t oldYCell = bullet->y >> 6;
		uint8_t xMoved = oldXCell != ((bullet->x += bullet->vX) >> 6);
		uint8_t yMoved = oldYCell != ((bullet->y += bullet->vY) >> 6);

		if ((bullet->y >> 6) >= config->winH ||
			detectHit(config, state, bullet, ship))
		{ // Reached bottom or dead
			blitBullet(bullet, ERASE);
		}

        if ((bullet->y >> 6) <= 0 || (bullet->y >> 6) >= config->winH ||
            (bullet->x >> 6) <  0 || (bullet->x >> 6) >= config->winW) {
            blitBullet(bullet, ERASE);
            bullet->active = 0;
        }
        else if (xMoved || yMoved)
        {
        	blitBullet(bullet, ERASE);
            blitBullet(bullet, DRAW);
        }
    }
}

static uint8_t detectHit(const gameConfig_t *config, gameState_t *state, bullet_t *bullet, spaceship_t *ship) {

	/* Check for ufo hit */
	for (uint8_t i = 0; i < config->maxUfos; i++) {
		ufo_t *ufo = &state->ufoArray[i];

		if (!ufo->active || ufo->lives <= 0) continue; // Skip non-initialized or dead UFO's

		if (bullet->x >= ufo->x &&
		    bullet->x <  ufo->x + (SPRITE_UFO_W<< 6) &&
		    bullet->y >= ufo->y &&
		    bullet->y <  ufo->y + (SPRITE_UFO_H << 6))
		{
		    ufo->lives--;
		    return 1;
		}
	}

	/* Check for asteroid hit */
	for (uint8_t i = 0; i < config->maxAsteroids; i++) {
		asteroid_t *asteroid = &state->asteroidArray[i];

		if (!asteroid->active || asteroid->lives <= 0) continue; // Skip non-initialized or dead asteroids

		if (bullet->x >= asteroid->x &&
		    bullet->x <  asteroid->x + (SPRITE_AST_W << 6) &&
		    bullet->y >= asteroid->y &&
		    bullet->y <  asteroid->y + (SPRITE_AST_H << 6))
		{
		    asteroid->lives--;
		    return 1;
		}
	}
	// Check for spaceship hit
	if (bullet->x >= ship->x &&
	    bullet->x <  ship->x + (SPRITE_SHIP_W << 6) &&
	    bullet->y >= ship->y &&
	    bullet->y <  ship->y + (SPRITE_SHIP_H << 6))
	{
	    if (state->lives > 0) {
	        state->lives--;
	    }

	    hudLoseLife();
	    return 1;
	}



	return 0;
}


/* ----------- SPACESHIP ---------- */


void updateSpaceshipShotAngle(spaceship_t *ship)
{
    ship->shot_Angle++;

    if (ship->shot_Angle > 4) {
        ship->shot_Angle = 0;
    }
}


void addSpaceship(spaceship_t *ship, int16_t startX, int16_t startY) {
    // Initialize position
    ship->x = startX;
    ship->y = startY;

    // Initialize movement
    ship->vX = 0;
    ship->vY = 0;

    // Initial state
    ship->lvl = 0;
    ship->powerUp = 0;
    ship->shot_Angle = 0;

    // Draw spaceship
    blitSpaceship(ship, DRAW);
}




void updateSpaceship(const gameConfig_t *config, spaceship_t *ship, bullet_t *bulletArray)
{
    /* Read joystick */
    uint8_t inputX = readPotXaxis();
    uint8_t inputY = readPotYaxis();
    uint8_t inputWhiteButton = readButton(1);


    if (inputX == 0)      ship->vX = (int16_t)( 1 << 6);
    else if (inputX == 1) ship->vX = (int16_t)(-1 << 6);
    else                  ship->vX = 0; /* Default: stop */

    if (ship->vX != 0){
    	ship->x = (int16_t)(ship->x + ship->vX);
    	blitSpaceship(ship, ERASE);
        blitSpaceship(ship, DRAW); // Draw updated position

    }

    /* Shooting ability */
    static uint8_t prevWhiteButton = 0;
    static uint8_t prevInputY = 2;

    if (inputY == 0 && prevInputY != 0) {
        updateSpaceshipShotAngle(ship);
    }

    prevInputY = inputY;

    if (inputWhiteButton && !prevWhiteButton) {

        int16_t vX = 0;
        int16_t vY = -1 << 5;

        switch (ship->shot_Angle) {
            case 0: vX = 0; break;
            case 1: vX = 1 << 6; break;
            case 2: vX = 3 << 6; break;
            case 3: vX = -1 << 6; break;
            case 4: vX = -3 << 6; break;
        }

        addBullet(
        	config,
			bulletArray,
            ship->x + (SPRITE_SHIP_W << 5),
            ship->y-1,
            vX,
            vY
        );
    }
    prevWhiteButton = inputWhiteButton;
}









