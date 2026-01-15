#include "render.h"


/* ---------- SPACESHIP ---------- */
#define SHIP_H 4 // REMEMBER TO UPDATE IN SPRITES.H
#define SHIP_W 7 // REMEMBER TO UPDATE IN SPRITES.H

void drawSpaceship(const spaceship_t *ship) {
	goTo(ship->x, ship->y);

	const uint8_t (*shipSprite)[SPR_W];
	const uint8_t (*powerUpSprite)[SPR_W] = NULL;

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
    for (uint8_t row = 0; row < SPR_H; row++) {
        for (uint8_t col = 0; col < SPR_W; col++) {

            uint8_t color;

            // we want to print the powerUp sprite on top of the ships sprite
            if (powerUpSprite && powerUpSprite[row][col] != 0) {
                color = powerUpSprite[row][col];
            } else {
                color = shipSprite[row][col];
            }

            if (color == 0) continue;  // transparent -> do nothing

            goTo(ship->x + col, ship->y + row);
            bgColor(color);
            printf(" ");
        }
    }

    resetBgColor();
}
