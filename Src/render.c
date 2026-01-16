#include "render.h"


/* ---------- ASTEROID ---------- */
#define AST_H 6 // REMEMBER TO UPDATE IN SPRITES.H
#define AST_W 8 // REMEMBER TO UPDATE IN SPRITES.H

void blitAsteroid(const asteroid_t *asteroid, blitMode_t mode) {
	const uint8_t (*astroidSprite)[AST_W];

	// Find level sprite in LUT
	uint8_t safeAsteroid = asteroid->type > 1 ? 1 : asteroid->type; // cap at 2 types
	astroidSprite = asteroidSprites[safeAsteroid];

   // Render sprite, we only update non-zero pixels for efficiency
	for (int16_t row = 0; row < AST_H; row++) {

		int16_t fpRow = row<<6; // Only calc fixed point row once every row

		for (int16_t col = 0; col < AST_W; col++) {
			uint8_t color = astroidSprite[row][col];

			if (color == 0) continue;  // transparent -> do nothing


			int16_t nextX = asteroid->x;
			int16_t nextY = asteroid->y;

			if (mode == ERASE) {

				// Go to last position
				nextX -= asteroid->vX;
				nextY -= asteroid->vY;

				resetBgColor();
			} else {
				bgColor(color);
			}

			// Also convert col to Q10.6
			goToCoords(nextX + (col << 6), nextY + fpRow);
			printf(" ");
		}
	}
}


/* ---------- SPACESHIP ---------- */
#define SHIP_H 4 // REMEMBER TO UPDATE IN SPRITES.H
#define SHIP_W 7 // REMEMBER TO UPDATE IN SPRITES.H

void blitSpaceship(const spaceship_t *ship, blitMode_t mode) {
	const uint8_t (*shipSprite)[SHIP_W];
	const uint8_t (*powerUpSprite)[SHIP_W] = NULL;

	// Only look up sprite if power up is active
	if (ship->powerUp) {
		// Find power up sprite in LUT
		uint8_t safePowerUp = ship->powerUp  > 4 ? 4 : ship->powerUp; // cap at 4 powerUps
		powerUpSprite = shipPowerUpSprites[--safePowerUp]; // Array is zero-index, so we detract one
	}

	// Find level sprite in LUT
	uint8_t safeLevel = ship->lvl > 3 ? 3 : ship->lvl; // cap at level 3
	shipSprite = shipLevelSprites[safeLevel]; // Your allowed to be level 0 here, so no -1


    // Render sprite, we only update non-zero pixels for efficiency
    for (uint8_t row = 0; row < SHIP_H; row++) {
        for (uint8_t col = 0; col < SHIP_W; col++) {

            uint8_t color;

            // we want to print the powerUp sprite on top of the ships sprite
            if (powerUpSprite && powerUpSprite[row][col] != 0) {
                color = powerUpSprite[row][col];
            } else {
                color = shipSprite[row][col];
            }

            if (color == 0) continue;  // transparent -> do nothing

            goTo(ship->x + col, ship->y + row);
            mode == DRAW ? bgColor(color) : resetBgColor();
            printf(" ");
        }
    }
}


/* ---------- UFO ---------- */
#define UFO_H 2 // REMEMBER TO UPDATE IN SPRITES.H
#define UFO_W 3 // REMEMBER TO UPDATE IN SPRITES.H

void blitUfo(const ufo_t *ufo, blitMode_t mode) {
	const uint8_t (*ufoSprite)[UFO_W];

	// Find level sprite in LUT
	uint8_t safeType = ufo->type > 4 ? 4 : ufo->type; // cap at 5 types
	ufoSprite = ufoSprites[safeType]; // Your allowed to be level 0 here, so no -1

    // Render sprite, we only update non-zero pixels for efficiency
    for (uint8_t row = 0; row < UFO_H; row++) {
    	int16_t fpRow = row << 6;

        for (uint8_t col = 0; col < UFO_W; col++) {

            uint8_t color = ufoSprite[row][col];

            if (color == 0) continue;  // transparent -> do nothing

			int16_t nextX = ufo->x;
			int16_t nextY = ufo->y;

			if (mode == ERASE) {
				// Go to last position
				nextX -= ufo->vX;
				nextY -= ufo->vY;

				resetBgColor();
			} else {
				bgColor(color);
			}

            goToCoords(nextX + (col << 6), nextY + fpRow);
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
		nextX -= bullet->vX;
		nextY -= bullet->vY;

		resetBgColor();
	} else {
		fgColor(7);
		resetBgColor();
	}

	goToCoords(nextX, nextY);

	if (mode == ERASE) {
		putchar(' ');				// Delete bullet
	}
	else if (bullet->vX > 0) {
		putchar('/');				// If bullet is going to the right, turn bullet right
	} else if (bullet->vX < 0) {
		putchar('\\');				// If bullet is going to the left, turn bullet left
	} else {
		putchar('|');				// If bullet is going straight, straighten bullet
	}
}
