#include "sprites.h"



/* ---------- SPACESHIP ---------- */
#define SPR_H 4
#define SPR_W 5

static const uint8_t defaultShip[SPR_H][SPR_W] = {
	    {0, 0, 1, 0, 0},
	    {0, 1, 6, 1, 0},
	    {1, 1, 1, 1, 1},
	    {0, 3, 0, 3, 0}
};

void drawSpaceship(const spaceship_t *ship) {
	goTo(ship->x, ship->y);

	const uint8_t (*shipSprite)[SPR_W];

	// We prioritize drawing power up sprite over level sprite
	if (ship->powerUp) {
		switch (ship->powerUp) {
			case 1:
				// Power up 1 sprite
				break;
			case 2:
				// Power up 2sprite
				break;
			default:
				// Fallback power up sprite.
				// SHOULD NEVER GET CALLED.
				break;
		}
	}
	else {
		switch (ship->lvl) {
			case 0:
				shipSprite = defaultShip;
				break;
			case 1:
				// level 1 sprite
				break;
			case 2:
				// level 2 sprite
				break;
			default:
				// Fallback level sprite.
				// Golden ship or something
				break;
		}
	}

    // Render sprite, we only update non-zero pixels for effeciency
    for (uint8_t row = 0; row < SPR_H; row++) {
        for (uint8_t col = 0; col < SPR_W; col++) {

            uint8_t color = shipSprite[row][col];
            if (color == 0) continue;  // transparent -> do nothing

            goTo(ship->x + col, ship->y + row);
            bgColor(color);
            printf(" ");
        }
    }

    resetBgColor();
}
