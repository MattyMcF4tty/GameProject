#include "render.h"
#include "ansi.h"


/* ---------- ASTEROID ---------- */
void blitAsteroid(const gameConfig_t *config, const asteroid_t *asteroid, blitMode_t mode)
{
    uint8_t safeType = asteroid->type;
    if (safeType >= SPRITE_AST_TYPES) safeType = SPRITE_AST_TYPES - 1;

    const uint8_t (*asteroidSprite)[SPRITE_AST_W] = asteroidSprites[safeType];

    int16_t baseX = asteroid->x;
    int16_t baseY = asteroid->y;

    if (mode == ERASE) {
        baseX = (int16_t)(baseX - asteroid->vX);
        baseY = (int16_t)(baseY - asteroid->vY);
        resetBgColor();
    }

    // Clip rect in Q10.6 (interior of bordered window)
    const int16_t leftX   = (config->winStartX + 1) << 6;
    const int16_t rightX  = (config->winStartX + config->winW - 1) << 6;  // exclusive
    const int16_t topY    = (config->winStartY + 1) << 6;
    const int16_t bottomY = (config->winStartY + config->winH - SPRITE_AST_H - 2) << 6;  // exclusive

    for (int16_t row = 0; row < SPRITE_AST_H; row++) {
        const int16_t pixelY = (int16_t)(baseY + (row << 6));

        // Skip entire row if outside vertically
        if (pixelY <= topY || pixelY >= bottomY) continue;

        for (int16_t col = 0; col < SPRITE_AST_W; col++) {
            const uint8_t color = asteroidSprite[row][col];
            if (color == 0) continue;

            const int16_t pixelX = (int16_t)(baseX + (col << 6));

            // Skip pixel if outside horizontally
            if (pixelX < leftX || pixelX >= rightX) continue;

            if (mode == DRAW) bgColor(color);

            goToCoords(pixelX, pixelY);
            printf(" ");
        }
    }
}


/* ---------- SPACESHIP ---------- */
void blitSpaceship(const gameConfig_t *config, const spaceship_t *ship, blitMode_t mode, uint8_t prevPowerUp) {


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

    const int16_t leftX   = (int16_t)((config->winStartX + 1) << 6);
    const int16_t rightX  = (int16_t)((config->winStartX + config->winW - 1) << 6);
    const int16_t topY    = (int16_t)((config->winStartY + 1) << 6);
    const int16_t bottomY = (int16_t)((config->winStartY + config->winH - 2) << 6);

    // Render sprite, we only update non-zero pixels for efficiency
    for (uint8_t row = 0; row < SPRITE_SHIP_H; row++) {
    	int16_t fpRow = (int16_t)(row << 6); // Only calculate row position once per row
        const int16_t pixelY = (int16_t)(baseY + ((int16_t)row << 6));

        if (pixelY < topY || pixelY >= bottomY) continue;

        for (uint8_t col = 0; col < SPRITE_SHIP_W; col++) {
            const int16_t pixelX = (int16_t)(baseX + ((int16_t)col << 6));

            // Clip horizontally
            if (pixelX < leftX || pixelX >= rightX) continue;

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
void blitUfo(const gameConfig_t *config, const ufo_t *ufo, blitMode_t mode)
{
    // Validate type
    uint8_t safeType = ufo->type;
    if (safeType >= SPRITE_UFO_TYPES) {
        safeType = SPRITE_UFO_TYPES - 1;
    }
    const uint8_t (*ufoSprite)[SPRITE_UFO_W] = ufoSprites[safeType];

    // Base position (Q10.6)
    int16_t baseX = ufo->x;
    int16_t baseY = ufo->y;

    if (mode == ERASE) {
        baseX = (int16_t)(baseX - ufo->vX);
        baseY = (int16_t)(baseY - ufo->vY);
        resetBgColor();
    }

    // Clip rect in Q10.6 (interior of bordered window)
    const int16_t leftX   = (config->winStartX + 1) << 6;
    const int16_t rightX  = (config->winStartX + config->winW - 1) << 6;  // exclusive
    const int16_t topY    = (config->winStartY + 1) << 6;
    const int16_t bottomY = (config->winStartY + config->winH - SPRITE_UFO_H - 6) << 6;  // exclusive

    for (uint8_t row = 0; row < SPRITE_UFO_H; row++) {
        const int16_t pixelY = baseY + (row << 6);

        // Skip entire row if outside vertically
        if (pixelY < topY || pixelY >= bottomY) continue;

        for (uint8_t col = 0; col < SPRITE_UFO_W; col++) {
            const uint8_t color = ufoSprite[row][col];
            if (color == 0) continue;

            const int16_t pixelX = baseX + (col << 6);

            // Skip pixel if outside horizontally
            if (pixelX < leftX || pixelX >= rightX) continue;

            if (mode == DRAW) {
                bgColor(color);
            }

            goToCoords(pixelX, pixelY);
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
