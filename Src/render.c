#include "render.h"
#include "ansi.h"


/* ---------- ASTEROID ---------- */
void blitAsteroid(const asteroid_t *asteroid, blitMode_t mode) {

    // Validate type
    uint8_t safeType = asteroid->type;
    if (safeType >= SPRITE_AST_TYPES) {
        safeType = SPRITE_AST_TYPES - 1; // Zero indexed
    }

    // Find type in sprite LUT
    const uint8_t (*asteroidSprite)[SPRITE_AST_W] = asteroidSprites[safeType];

    // Compute base position once
    int16_t baseX = asteroid->x;
    int16_t baseY = asteroid->y;

    if (mode == ERASE) {
        baseX = (int16_t)(baseX - asteroid->vX);
        baseY = (int16_t)(baseY - asteroid->vY);
        resetBgColor(); // Only write to terminal once, for efficiency
    }

    for (int16_t row = 0; row < SPRITE_AST_H; row++) {
        int16_t fpRow = (int16_t)(row << 6); // Only calculate row position once per row

        for (int16_t col = 0; col < SPRITE_AST_W; col++) {
            uint8_t color = asteroidSprite[row][col];

            if (color == 0) continue;  // transparent

            if (mode == DRAW) {
                bgColor(color);
            }

            goToCoords((int16_t)(baseX + (col << 6)), (int16_t)(baseY + fpRow));
            printf(" ");
        }
    }
}


/* ---------- SPACESHIP ---------- */
void blitSpaceship(const spaceship_t *ship, blitMode_t mode, uint8_t prevPowerUp) {


    uint8_t powerUpState = (mode == ERASE) ? prevPowerUp : ship->powerUp;

	// Only look up sprite if power up is active
	const uint8_t (*powerUpSprite)[SPRITE_SHIP_W] = NULL;

	if (powerUpState != 0) {

	    uint8_t safePowerUp = powerUpState - 1; // Zero indexed

	    if (safePowerUp > SPRITE_SHIP_POWER_UPS) {
	        safePowerUp = SPRITE_SHIP_POWER_UPS - 1; // Zero indexed
	    }

	    powerUpSprite = shipPowerUpSprites[safePowerUp];
	}

	// Find level sprite in LUT
	uint8_t safeLevel = ship->lvl;
	if (safeLevel >= SPRITE_SHIP_LEVELS) {
		safeLevel = SPRITE_SHIP_LEVELS - 1;
	}
	const uint8_t (*shipSprite)[SPRITE_SHIP_W] = shipLevelSprites[safeLevel];

    // Compute base position once
    int16_t baseX = ship->x;
    int16_t baseY = ship->y;

    if (mode == ERASE) {
        baseX = (int16_t)(baseX - ship->vX);
        baseY = (int16_t)(baseY - ship->vY);
        resetBgColor(); // Only write to terminal once, for efficiency
    }

    // Render sprite, we only update non-zero pixels for efficiency
    for (uint8_t row = 0; row < SPRITE_SHIP_H; row++) {
    	int16_t fpRow = (int16_t)(row << 6); // Only calculate row position once per row

        for (uint8_t col = 0; col < SPRITE_SHIP_W; col++) {

            uint8_t color;

            // we want to print the powerUp sprite on top of the ships sprite
            if (powerUpSprite && powerUpSprite[row][col] != 0) {
                color = powerUpSprite[row][col];
            } else {
                color = shipSprite[row][col];
            }

            if (color == 0) continue;  // transparent

            if (mode == DRAW) {
                bgColor(color);
            }

            goToCoords(baseX + (col << 6), baseY + fpRow);
            printf(" ");
        }
    }
}


/* ---------- UFO ---------- */
void blitUfo(const ufo_t *ufo, blitMode_t mode) {

	// Find level sprite in LUT
	uint8_t safeType = ufo->type;
	if (ufo->type >= SPRITE_UFO_TYPES) {
		safeType = SPRITE_UFO_TYPES - 1; // Zero indexed
	}

	const uint8_t (*ufoSprite)[SPRITE_UFO_W] = ufoSprites[safeType];

	// Compute base position once
	int16_t baseX = ufo->x;
	int16_t baseY = ufo->y;

	if (mode == ERASE) {
		baseX = (int16_t)(baseX - ufo->vX);
		baseY = (int16_t)(baseY - ufo->vY);
		resetBgColor(); // Only write to terminal once, for efficiency
	}

    // Render sprite, we only update non-zero pixels for efficiency
    for (uint8_t row = 0; row < SPRITE_UFO_H; row++) {
    	int16_t fpRow = row << 6;

        for (uint8_t col = 0; col < SPRITE_UFO_W; col++) {
            uint8_t color = ufoSprite[row][col];

            if (color == 0) continue;  // transparent

            if (mode == DRAW) {
                bgColor(color);
            }

            goToCoords(baseX + (col << 6), baseY + fpRow);
            printf(" ");
        }
    }
}


/* ---------- BULLET ---------- */
void blitBullet(const bullet_t *bullet, blitMode_t mode) {

    int16_t nextX = bullet->x;
    int16_t nextY = bullet->y;

    if (mode == ERASE) {
        // Go to last position
        nextX = (nextX - bullet->vX);
        nextY = (nextY - bullet->vY);
        resetBgColor();

    } else {
        resetBgColor();
    	switch (bullet->type) {
    	case (0):
			fgColor(7);
			break;
    	case (1): // MORE DAMAGE
			fgColor(1);
    		break;
    	case (2): // MORE SPEED
			fgColor(6);
    		break;
    	default:
            fgColor(7);
    		break;
    	}
    }

    goToCoords(nextX, nextY);

    if (mode == ERASE) {
        printf(" ");
        return;
    }

    // Determination of direction. We ignore small changes
    int16_t vx = (bullet->vX >> 2);
    int16_t vy = (bullet->vY >> 2);

    int8_t dirX = 0;
    int8_t dirY = 0;

    if (vx > 0) dirX = 1;
    else if (vx < 0) dirX = -1;

    if (vy > 0) dirY = 1;
    else if (vy < 0) dirY = -1;

    // Determine bullet "sprite"
    char c;
    if (dirX == 0 && dirY == 0) {
        c = '.';                 // Not moving
    } else if (dirX == 0) {
        c = '|';                 // vertical
    } else if (dirY == 0) {
        c = '-';                 // horizontal
    } else if (dirX == dirY) {
        c = '\\';                // down-right or up-left
    } else {
        c = '/';                 // up-right or down-left
    }

    printf("%c", c);
}

/* ---------- POWERUP ---------- */
void blitPowerUp(const power_up_t *powerUp, blitMode_t mode) {
	resetBgColor();

	// Find powerUp sprite in LUT
	uint8_t safeType = powerUp->type;
	if (powerUp->type >= SPRITE_POWER_UP_TYPES) {
		safeType = SPRITE_POWER_UP_TYPES - 1; // Zero indexed
	}

	const char (*powerUpSpriteChar)[SPRITE_POWER_UP_W] = powerUpSpritesChar[safeType];
	const uint8_t (*powerUpSpriteColor)[SPRITE_POWER_UP_W] = powerUpSpritesColor[safeType];

	// Compute base position once
	int16_t baseX = powerUp->x;
	int16_t baseY = powerUp->y;

	char cellChar = ' ';

	if (mode == ERASE) {
		baseX = baseX - powerUp->vX;
		baseY = baseY - powerUp->vY;
	}

    // Render sprite, we only update non-zero pixels for efficiency
    for (uint8_t row = 0; row < SPRITE_POWER_UP_H; row++) {
    	int16_t fpRow = row << 6;

        for (uint8_t col = 0; col < SPRITE_POWER_UP_W; col++) {
        	char c = powerUpSpriteChar[row][col];

            if (c == ' ') continue;  // transparent

            if (mode == DRAW) {
            	cellChar = c;
            	uint8_t color = powerUpSpriteColor[row][col];
                fgColor(color);
            }

            goToCoords(baseX + (col << 6), baseY + fpRow);
            printf("%c", cellChar);
        }
    }
}
