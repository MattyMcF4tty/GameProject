#include "render.h"


/* ---------- ASTEROID ---------- */
#define AST_H 6 // REMEMBER TO UPDATE IN SPRITES.H
#define AST_W 8 // REMEMBER TO UPDATE IN SPRITES.H

void blitAsteroid(const asteroid_t *asteroid, blitMode_t mode) {
	goTo(asteroid->x, asteroid->y);

	const uint8_t (*astroidSprite)[AST_W];

	// Find level sprite in LUT
	uint8_t safeAsteroid = asteroid->type > 1 ? 1 : asteroid->type; // cap at 2 asteroids
	astroidSprite = asteroidSprites[safeAsteroid];

   // Render sprite, we only update non-zero pixels for efficiency
	for (uint8_t row = 0; row < AST_H; row++) {
		for (uint8_t col = 0; col < AST_W; col++) {
			uint8_t color = astroidSprite[row][col];

			if (color == 0) continue;  // transparent -> do nothing

			goTo(asteroid->x + col, asteroid->y + row);
			mode == DRAW ? bgColor(color) : resetBgColor();
			printf(" ");
		}
	}

	resetBgColor(); // -- Reset bg color just to be safe
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

    resetBgColor(); // -- Reset bg color just to be safe
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
        for (uint8_t col = 0; col < UFO_W; col++) {

            uint8_t color = ufoSprite[row][col];

            if (color == 0) continue;  // transparent -> do nothing

            goTo(ufo->x + col, ufo->y + row);
            mode == DRAW ? bgColor(color) : resetBgColor();
            printf(" ");
        }
    }

    resetBgColor(); // -- Reset bg color just to be safe
}


/* ---------- BULLET ---------- */
void blitBullet(const bullet_t *bullet, blitMode_t mode) {
	goTo(bullet->x, bullet->y);

	mode == DRAW ? bgColor(7) : resetBgColor();
	printf(" ");

	resetBgColor(); // -- Reset bg color just to be safe
}
