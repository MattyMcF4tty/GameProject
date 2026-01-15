#include "game_master.h"
#include "render.h"



/* ----------- RANDOMNESS ---------- */
static uint32_t randomRange(uint32_t min, uint32_t max) {
    if (max < min) {
        return min;  // or swap, or assert
    }

    uint32_t span = max - min + 1;
    return min + ((uint32_t)rand() % span);
}


/* ----------- ASTEROID ---------- */
static asteroid_t asteroidArray[MAX_ASTEROIDS] = {0};

void addAsteroid() {
	uint8_t randX = (uint8_t)randomRange(0, 200);
	uint32_t randVY = randomRange(1, 3);
	uint8_t randType = (uint8_t)randomRange(0, 1);

	for (uint8_t i = 0; i < MAX_ASTEROIDS; i++) {
		asteroid_t *asteroid = &asteroidArray[i];

		if (!asteroid->active) {
			asteroid->active = 1;
			asteroid->x = randX;
			asteroid->y = 0;
			asteroid->vX = 0;
			asteroid->vY = randVY;
			asteroid->type = randType;
			break;
		}
	}
}


void moveAsteroids() {
	for (uint8_t i = 0; i < MAX_ASTEROIDS; i++) {
		asteroid_t *asteroid = &asteroidArray[i];

		if (asteroid->active) {
			blitAsteroid(asteroid, ERASE);

			asteroid->x += asteroid->vX;
			asteroid->y += asteroid->vY;

			blitAsteroid(asteroid, DRAW);
		}
	}
}

