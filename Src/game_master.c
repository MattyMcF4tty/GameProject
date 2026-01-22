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
static void updateAsteroids(const gameConfig_t *config, asteroid_t *asteroidArray, power_up_t *powerUpArray);

static void addUfo(const gameConfig_t *config, ufo_t *ufoArray);
static void updateUfos(const gameConfig_t *config, ufo_t *ufoArray, bullet_t *bulletArray, uint8_t *lives, uint32_t *score);

static void addBullet(const gameConfig_t *config, bullet_t *bulletArray, uint8_t type, int16_t x, int16_t y, int16_t vX, int16_t vY);
static void updateBullets(const gameConfig_t *config, gameState_t *state, spaceship_t *ship, uint8_t *lives);
static uint8_t detectHit(const gameConfig_t *config, gameState_t *state, bullet_t *bullet, spaceship_t *ship);

static void addSpaceship(spaceship_t *ship, int16_t startX, int16_t startY);
static void updateSpaceship(const gameConfig_t *config, spaceship_t *ship, bullet_t *bulletArray, const joystick_input_t *joyInput);

static void addPowerUp(const gameConfig_t *config, power_up_t *powerUpArray, uint8_t type, int16_t x, int16_t y);
static void updatePowerUps(const gameConfig_t *config, power_up_t *powerUpArray, spaceship_t *ship);

/* ---------- Public functions ---------- */
uint8_t initGameState(const gameConfig_t *config, gameState_t *state)
{

	// We allocate the needed memory for game
	state->ufoArray 		= calloc(config->maxUfos, sizeof(ufo_t));
	state->asteroidArray 	= calloc(config->maxAsteroids, sizeof(asteroid_t));
	state->bulletArray 		= calloc(config->maxBullets, sizeof(bullet_t));
	state->powerUpArray 	= calloc(config->maxPowerUps, sizeof(power_up_t));
	state->ship 			= calloc(1, sizeof(spaceship_t));

	if (!state->ufoArray || !state->asteroidArray || !state->bulletArray || !state->ship)
	{
		// Allocation failed, clean up

		free(state->ufoArray);
		free(state->asteroidArray);
		free(state->bulletArray);
		free(state->ship);

		return 1;
	}

	// Init spaceship
	addSpaceship(state->ship,
				 (int16_t)((config->winStartX + config->winW) << 5),
				 (int16_t)(config->winH - SPRITE_SHIP_H) << 6);

	// Set game values
	state->lives = 3;
	state->score = 0;

	lcdTextInit();

	return 0;
}

void updateGameState(const gameConfig_t *config, gameState_t *state, const joystick_input_t *joyInput)
{
	entitySpawner(config, state); // Spawn asteroids and UFO's

	updateSpaceship(config, state->ship, state->bulletArray, joyInput);
	updateAsteroids(config, state->asteroidArray, state->powerUpArray);
	updateUfos(config, state->ufoArray, state->bulletArray, &state->lives, &state->score);
	updateBullets(config, state, state->ship, &state->lives);
	updatePowerUps(config, state->powerUpArray, state->ship);

	if (state->lives <= 0) { // Game over if player is dead
		state->screen = GAME_OVER;

		if (state->score > state->highScore) state->highScore = state->score; // update highscore
	}

	if 		(state->score > 100) state->level = 1;
	else if (state->score > 200) state->level = 2;
	else if (state->score > 300) state->level = 3;
}

/*------------ Local functions ---------- */
static void entitySpawner(const gameConfig_t *config, gameState_t *state)
{
	uint16_t spawnRoll = (uint16_t)randomRange(0, 1000);

	uint16_t asteroidSpawnRate;
	uint16_t ufoSpawnRate;
	switch(state->level) {
		case (0):
			asteroidSpawnRate = 5;  // 0.5%
			ufoSpawnRate 	  = 10; // 1%
			state->ship->lvl  = 0;
			break;
		case (1):
			asteroidSpawnRate = 10; // 1%
			ufoSpawnRate 	  = 50; // 5%
			state->ship->lvl  = 1;
			break;
		case (2):
			asteroidSpawnRate = 20;  // 2%
			ufoSpawnRate 	  = 100; // 10%
			state->ship->lvl  = 2;
			break;
		default:
			asteroidSpawnRate = 50;  // 5%
			ufoSpawnRate 	  = 150; // 15%
			state->ship->lvl  = 3;
			break;
	}

	if (spawnRoll <= asteroidSpawnRate)
	{
		addAsteroid(config, state->asteroidArray);
	}
	if (spawnRoll <= ufoSpawnRate)
	{
		addUfo(config, state->ufoArray);
	}
}

/* ----------- ASTEROID ---------- */
static void addAsteroid(const gameConfig_t *config, asteroid_t *asteroidArray)
{
	for (uint8_t i = 0; i < config->maxAsteroids; i++)
	{
		asteroid_t *asteroid = &asteroidArray[i];

		if (asteroid->active)
			continue; // Skip if index already initialized

		uint8_t randType = (uint8_t)randomRange(0, 1);

		int16_t spawnArea = (int16_t)randomRange((config->winStartX+1) << 6,
												 (config->winW-SPRITE_AST_W) << 6);

		asteroid->active = 1;
		asteroid->lives = 10;
		asteroid->x = spawnArea; ; // Spawn within 1 -> width
		asteroid->y = (config->winStartY-SPRITE_AST_H) << 6; // Q10.6
		asteroid->vX = 0;
		asteroid->vY = (int16_t)randomRange(1 << 2, 1 << 4); // speed: 1/32 -> 1/4
		asteroid->type = randType;
		asteroid->gravity = (int16_t)randomRange(1 << 4, 1 << 5); // 1/4 -> 1/2

		break; // Stop after initialization
	}
}

static void updateAsteroids(const gameConfig_t *config, asteroid_t *asteroidArray, power_up_t *powerUpArray)
{
	for (uint8_t i = 0; i < config->maxAsteroids; i++)
	{
		asteroid_t *asteroid = &asteroidArray[i];

		if (!asteroid->active)
			continue; // Skip non-initialized asteroids

		int16_t oldXCell = asteroid->x >> 6;
		int16_t oldYCell = asteroid->y >> 6;

		// Detect if asteroid should be redrawn in a different cell
		asteroid->x += asteroid->vX;
		asteroid->y += asteroid->vY;
		uint8_t xMoved = oldXCell != (asteroid->x >> 6);
		uint8_t yMoved = oldYCell != (asteroid->y >> 6);

		if (asteroid->lives <= 0)
		{ // dead

			switch (asteroid->type) {
				case (0): // Asteroid -> MORE DAMAGE
					addPowerUp(config, powerUpArray, 0, asteroid->x, asteroid->y);
					break;
				case (1): // Satellite -> MORE DAMAGE
					addPowerUp(config, powerUpArray, 1, asteroid->x, asteroid->y);
					break;
			}

			blitAsteroid(config, asteroid, ERASE);

			asteroid->active = 0;
		}
		else if ((asteroid->y >> 6) >= config->winH)
		{ // Reached bottom
			blitAsteroid(config, asteroid, ERASE);

			asteroid->active = 0;
		}
		else
		{
			if (xMoved || yMoved)
			{
				blitAsteroid(config, asteroid, ERASE);
				blitAsteroid(config, asteroid, DRAW);
			}
		}
	}
}

/* ----------- UFOS ---------- */
static void addUfo(const gameConfig_t *config, ufo_t *ufoArray)
{
	for (uint8_t i = 0; i < config->maxUfos; i++)
	{
		ufo_t *ufo = &ufoArray[i];

		if (ufo->active)
			continue; // Skip if index already initialized

		uint8_t randType = (uint8_t)randomRange(0, 4);

		ufo->active = 1;
		ufo->lives = 3;
		ufo->x = (int16_t)randomRange((config->winStartX+1) << 6, config->winW << 6); // Spawn within 1 -> width
		ufo->y = (config->winStartY + 1) << 6; // Q10.6
		ufo->vX = 0;
		ufo->vY = (int16_t)randomRange(1 << 2, 1 << 3); // speed: 1/32 -> 1/16
		ufo->type = randType;
		ufo->shotDelay = (randType + 1) << 6; // Aggressiveness based of type

		break; // Stop after initialization
	}
}

static void updateUfos(const gameConfig_t *config, ufo_t *ufoArray, bullet_t *bulletArray, uint8_t *lives, uint32_t *score)
{
	for (uint8_t i = 0; i < config->maxUfos; i++)
	{
		ufo_t *ufo = &ufoArray[i];

		if (!ufo->active)
			continue; // Skip non-initialized UFO's

		// Detect if UFO should be redrawn in a different cell
		int16_t oldXCell = ufo->x >> 6;
		int16_t oldYCell = ufo->y >> 6;
		uint8_t xMoved = oldXCell != ((ufo->x += ufo->vX) >> 6);
		uint8_t yMoved = oldYCell != ((ufo->y += ufo->vY) >> 6);

		if (ufo->lives <= 0)
		{ // Dead
			blitUfo(config, ufo, ERASE);
			ufo->active = 0;
			*score += 10;

		}

		else if ((ufo->y >> 6) >= config->winH)
		{ // Hit bottom
			blitUfo(config, ufo, ERASE);
			ufo->active = 0;

			if (*lives > 0)
			{
				*lives -= 1;
			}

			hudLoseLife();
		}

		else
		{
			if (xMoved || yMoved)
			{
				blitUfo(config, ufo, ERASE);
				blitUfo(config, ufo, DRAW);
			}
			ufo->shotDelay--;
			if (ufo->shotDelay == 0)
			{
				int16_t bulletX = ufo->x + (1 << 6);
				int16_t bulletY = ufo->y + (2 << 6);

				addBullet(config, bulletArray, 0, bulletX, bulletY, 0, ufo->vY);

				ufo->shotDelay = (ufo->type + 1) << 4; // Reset shotDelay
			}
		}
	}
}

/* ----------- BULLETS ---------- */
static void addBullet(const gameConfig_t *config, bullet_t *bulletArray, uint8_t type,
                      int16_t x, int16_t y, int16_t vX, int16_t vY)
{
    for (uint8_t i = 0; i < config->maxBullets; i++)
    {
        bullet_t *bullet = &bulletArray[i];
        if (bullet->active) continue;

        // Base speed is 1 cell/frame in the same direction as the input vY sign
        int16_t speed = (1 << 6);

        // MORE SPEED (type==2): increase speed by 0.5 cell/frame
        if (type == 2) speed = (int16_t)(speed + (1 << 5));

        // Keep direction from caller: ship passes negative, UFO passes positive
        bullet->vY = (vY < 0) ? (int16_t)(-speed) : (int16_t)(+speed);

        bullet->active = 1;
        bullet->type   = type;
        bullet->dmg    = (type == 1) ? 2 : 1;  // MORE DAMAGE (type==1)
        bullet->x      = x;
        bullet->y      = y;
        bullet->vX     = vX;

        break;
    }
}

static void updateBullets(const gameConfig_t *config, gameState_t *state, spaceship_t *ship, uint8_t *lives)
{
	for (uint8_t i = 0; i < config->maxBullets; i++)
	{
		bullet_t *bullet = &state->bulletArray[i];

		if (!bullet->active)
			continue; // Skip non-initialized bullets

		for (uint8_t astIndex = 0; astIndex < config->maxAsteroids; astIndex++)
		{
			asteroid_t *asteroid = &state->asteroidArray[astIndex];

			if (!asteroid->active)
				continue; // Skip non-initialized asteroids

			applyAsteroidGravity(bullet, asteroid);
		}

		// Detect if bullet should be redrawn in a new cell
		int16_t oldXCell = bullet->x >> 6;
		int16_t oldYCell = bullet->y >> 6;
		uint8_t xMoved = oldXCell != ((bullet->x += bullet->vX) >> 6);
		uint8_t yMoved = oldYCell != ((bullet->y += bullet->vY) >> 6);

		int16_t bx = (int16_t)(bullet->x >> 6);
		int16_t by = (int16_t)(bullet->y >> 6);

		const int16_t minX = (int16_t)(config->winStartX);
		const int16_t maxX = (int16_t)(config->winStartX + config->winW - 2);
		const int16_t minY = (int16_t)(config->winStartY);
		const int16_t maxY = (int16_t)(config->winStartY + config->winH - 8);

		const uint8_t outOfBounds =
		    (bx <= minX) || (bx >= maxX) ||
		    (by <= minY) || (by >= maxY);

		if (detectHit(config, state, bullet, ship) || outOfBounds)
		{
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

static uint8_t detectHit(const gameConfig_t *config, gameState_t *state, bullet_t *bullet, spaceship_t *ship)
{

	/* Check for ufo hit */
	for (uint8_t i = 0; i < config->maxUfos; i++)
	{
		ufo_t *ufo = &state->ufoArray[i];

		if (!ufo->active || ufo->lives <= 0)
			continue; // Skip non-initialized or dead UFO's

		if (bullet->x >= ufo->x &&
			bullet->x < ufo->x + (SPRITE_UFO_W << 6) &&
			bullet->y >= ufo->y &&
			bullet->y < ufo->y + (SPRITE_UFO_H << 6))
		{
			if (bullet->dmg >= ufo->lives) {
			    ufo->lives = 0;
			} else {
			    ufo->lives -= bullet->dmg;
			}

			return 1;
		}
	}

	/* Check for asteroid hit */
	for (uint8_t i = 0; i < config->maxAsteroids; i++)
	{
		asteroid_t *asteroid = &state->asteroidArray[i];

		if (!asteroid->active || asteroid->lives <= 0)
			continue; // Skip non-initialized or dead asteroids

		if (bullet->x >= asteroid->x &&
			bullet->x < asteroid->x + (SPRITE_AST_W << 6) &&
			bullet->y >= asteroid->y &&
			bullet->y < asteroid->y + (SPRITE_AST_H << 6))
		{
			if (bullet->dmg >= asteroid->lives) {
				asteroid->lives = 0;
			} else {
				asteroid->lives -= bullet->dmg;
			}
			return 1;
		}
	}

	// Check for spaceship hit
	if (bullet->x >= ship->x &&
		bullet->x < ship->x + (SPRITE_SHIP_W << 6) &&
		bullet->y >= ship->y &&
		bullet->y < ship->y + (SPRITE_SHIP_H << 6))
	{
		if (bullet->dmg >= state->lives) {
			state->lives = 0;
		} else {
			state->lives -= bullet->dmg;
		}

		hudLoseLife();
		return 1;
	}

	return 0;
}

/* ----------- SPACESHIP ---------- */
static void addSpaceship(spaceship_t *ship, int16_t startX, int16_t startY)
{
	// Initialize position
	ship->x = startX;
	ship->y = startY;

	// Initialize movement
	ship->vX = 1 << 7;
	ship->vY = 0;

	// Initial state
	ship->lvl = 0;
	ship->powerUp = 0;
	ship->shotAngle = 2;  // Straight
}

static void updateSpaceship(const gameConfig_t *config, spaceship_t *ship, bullet_t *bulletArray, const joystick_input_t *joyInput)
{
	/* Read joystick */
	joystick_x_t inputX = joyInput->xAxis;
	joystick_y_t inputY = joyInput->yAxis;
	joystick_btn_t inputBtn = joyInput->button;

	uint8_t prevPowerUp = ship->powerUp;
	if (ship->powerUp != 0) {

		if (ship->powerUp == 2) ship->vX = 3 << 6; // set ship to move 3 cells per frame
		else ship->vX = 3 << 5; // set ship to move 1.5 cells per frame (default)

		if (ship->powerUpTime > 0) {
			ship->powerUpTime--;
		} else {
			ship->powerUp = 0;
		}
	}

	// Movement
	if (inputX != JOY_X_NONE) {

	    if (inputX == JOY_X_RIGHT)      ship->vX = abs(ship->vX);
	    else if (inputX == JOY_X_LEFT)  ship->vX = -abs(ship->vX);

	    // Window bounds in Q10.6, +2 we allow for the user to go a little out of bounds
	    // THis is so they can shoot the edges
	    const int16_t minX = (config->winStartX - 2) << 6;
	    const int16_t maxX = (config->winStartX + config->winW + 2 - SPRITE_SHIP_W) << 6;

	    int16_t newX = ship->x + ship->vX;

	    if (newX < minX) newX = minX;
	    else if (newX > maxX) newX = maxX;

	    if (newX != ship->x) {
	        ship->x = newX;
	        blitSpaceship(config, ship, ERASE, prevPowerUp);
	        blitSpaceship(config, ship, DRAW, prevPowerUp);
	    }
	}

	/* Shooting Angle */
	if (inputY != JOY_Y_NONE) {
		if (inputY == JOY_Y_UP) {
		    ship->shotAngle++;
		    if (ship->shotAngle > 4) ship->shotAngle = 0;
		}

		else if (inputY == JOY_Y_DOWN) {
		    if (ship->shotAngle == 0) ship->shotAngle = 4;
		    else ship->shotAngle--;
		}
	}

	/* Shooting */
	if (inputBtn == BTN_WHITE) // Remember to guard against user holding button down
	{

		int16_t vX = 0;
		int16_t vY = -1 << 5;

		switch (ship->shotAngle)
		{
		    case 4:  vX = -(3 << 6); break; // big left
		    case 3:  vX = -(1 << 6); break; // small left
		    case 2:  vX = 0;         break; // straight
		    case 1:  vX = +(1 << 6); break; // small right
		    case 0:  vX = +(3 << 6); break; // big right
		}

		addBullet(config, bulletArray, ship->powerUp,
		          ship->x + (SPRITE_SHIP_W << 5), 	// Middle of ship sprite
		          ship->y - (1 << 6),				// 1 cell above ship sprite
		          vX, vY);
	}


}

/* ---------- POWERUP ---------- */
static void addPowerUp(const gameConfig_t *config, power_up_t *powerUpArray, uint8_t type, int16_t x, int16_t y)
{
	for (uint8_t i = 0; i < config->maxPowerUps; i++)
	{
		power_up_t *powerUp = &powerUpArray[i];

		if (powerUp->active)
			continue; // Skip if index already initialized

		powerUp->active = 1;
		powerUp->type = type;
		powerUp->x = x;
		powerUp->y = y;
		powerUp->vX = 0;
		powerUp->vY = 1 << 6; // Power up moves 1 cell per frame

		break;
	}
}

static void updatePowerUps(const gameConfig_t *config, power_up_t *powerUpArray, spaceship_t *ship)
{
    // Ship AABB in cell space
    int16_t shipL = (int16_t)(ship->x >> 6);
    int16_t shipT = (int16_t)(ship->y >> 6);
    int16_t shipR = (int16_t)(shipL + SPRITE_SHIP_W);
    int16_t shipB = (int16_t)(shipT + SPRITE_SHIP_H);

    // Last valid top-left Y for the power-up (Q10.6)
    const int16_t bottomY = (int16_t)((config->winH - SPRITE_POWER_UP_H) << 6);

    for (uint8_t i = 0; i < config->maxPowerUps; i++)
    {
        power_up_t *powerUp = &powerUpArray[i];
        if (!powerUp->active) continue;

        int16_t oldXCell = powerUp->x >> 6;
        int16_t oldYCell = powerUp->y >> 6;

        // Move
        if (powerUp->y < bottomY) {
            powerUp->x += powerUp->vX;
            powerUp->y += powerUp->vY;
        }


        const uint8_t xMoved = (oldXCell != (powerUp->x >> 6));
        const uint8_t yMoved = (oldYCell != (powerUp->y >> 6));

        // Power-up AABB in cell space
        const int16_t puL = (int16_t)(powerUp->x >> 6);
        const int16_t puT = (int16_t)(powerUp->y >> 6);
        const int16_t puR = (int16_t)(puL + SPRITE_POWER_UP_W);
        const int16_t puB = (int16_t)(puT + SPRITE_POWER_UP_H);


        // Redraw if changed cell
        if (xMoved || yMoved) {
            blitPowerUp(powerUp, ERASE);
            blitPowerUp(powerUp, DRAW);
        }

        // Check if powerUp is getting picked up
        if (shipL < puR && shipR > puL && shipT < puB && shipB > puT) {
            blitPowerUp(powerUp, ERASE);
            powerUp->active = 0;
            ship->powerUp = powerUp->type + 1;
            ship->powerUpTime = 300; // 30 fps / 300 f = 10 seconds
            continue;
        }
    }
}
