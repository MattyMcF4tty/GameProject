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
	uint8_t randX = (uint8_t)randomRange(0, 200); // window width
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


void updateAsteroids() {
	for (uint8_t i = 0; i < MAX_ASTEROIDS; i++) {
		asteroid_t *asteroid = &asteroidArray[i];

		if (asteroid->active) {
			blitAsteroid(asteroid, ERASE);

			asteroid->x += asteroid->vX;
			asteroid->y += asteroid->vY;

			if (asteroid->y >= 50) { // window height
				asteroid->active = 0;
			} else {
				blitAsteroid(asteroid, DRAW);
			}
		}
	}
}


/* ----------- UFOS ---------- */
static ufo_t ufoArray[MAX_UFOS] = {0};

void addUfo() {
	uint8_t randX = (uint8_t)randomRange(1, 200); // window width
	uint32_t randVY = randomRange(1, 2);
	uint8_t randType = (uint8_t)randomRange(0, 4);


	for (uint8_t i = 0; i < MAX_UFOS; i++) {
		ufo_t *ufo = &ufoArray[i];

		if (!ufo->active) {
			ufo->active = 1;
			ufo->x = randX;
			ufo->y = 0;
			ufo->vX = 0;
			ufo->vY = randVY;
			ufo->type = randType;
			ufo->shotDelay = randType << 2;
			break;
		}
	}
}


void updateUfos() {
	for (uint8_t i = 0; i < MAX_UFOS; i++) {
		ufo_t *ufo = &ufoArray[i];

		if (ufo->active) {
			blitUfo(ufo, ERASE);

			ufo->x += ufo->vX;
			ufo->y += ufo->vY;

			if (ufo->y >= 50) { // window height
				ufo->active = 0;
			} else {
				blitUfo(ufo, DRAW);

				ufo->shotDelay--;
				if (ufo->shotDelay == 0) {
					ufo->shotDelay = ufo->type << 2;

					addBullet(ufo->x + (ufo->x >> 1), ufo->y+2, ufo->vY);
				}
			}
		}
	}
}


/* ----------- BULLETS ---------- */
static bullet_t bulletArray[MAX_BULLETS] = {0};

// VERY SIMPLE: SHOULD BE CHANGED
void addBullet(uint8_t x, uint8_t y, uint32_t vY) {
	vY = (vY + 1) << 1; // Make the bullet travel faster than whatever shot it.

	for (uint8_t i = 0; i < MAX_BULLETS; i++) {
		bullet_t *bullet = &bulletArray[i];

		if (!bullet->active) {
			bullet->active = 1;
			bullet->x = x;
			bullet->y = y;
			bullet->vX = 0;
			bullet->vY = vY;
			break;
		}
	}
}

void updateBullets() {
	for (uint8_t i = 0; i < MAX_BULLETS; i++) {
		bullet_t *bullet = &bulletArray[i];

		if (bullet->active) {
			blitBullet(bullet, ERASE);

			bullet->x += bullet->vX;
			bullet->y += bullet->vY;

			if (bullet->y >= 50) { // window height
				bullet->active = 0;
			} else {
				blitBullet(bullet, DRAW);
			}
		}
	}
}
