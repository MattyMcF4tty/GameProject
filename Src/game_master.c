#include "game_master.h"
#include "render.h"

#define TEMP_WIDTH 200
#define TEMP_HEIGHT 50

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
	for (uint8_t i = 0; i < MAX_ASTEROIDS; i++) {
		asteroid_t *asteroid = &asteroidArray[i];

		if (!asteroid->active) {
			asteroid->active = 1;
			asteroid->x = (int16_t)randomRange(1 << 6, TEMP_WIDTH << 6); // Spawn within 1 -> width
			asteroid->y = 0;
			asteroid->vX = 0;
			asteroid->vY = (int16_t)randomRange(1 << 4, 0x40); // Fastest speed is 1/4, slowest is 1/32 cells per frame.
			asteroid->type = (uint8_t)randomRange(0, 1);;
			break;
		}
	}
}


void updateAsteroids() {
	for (uint8_t i = 0; i < MAX_ASTEROIDS; i++) {
		asteroid_t *asteroid = &asteroidArray[i];

		if (!asteroid->active) continue; // Skip non-active asteroids

		int16_t oldXCell = asteroid->x >> 6;
		int16_t oldYCell = asteroid->y >> 6;

		asteroid->x += asteroid->vX;
		asteroid->y += asteroid->vY;

		uint8_t xMoved = oldXCell != (asteroid->x >> 6);
		uint8_t yMoved = oldYCell  != (asteroid->y >> 6);

		if ((asteroid->y >> 6) >= TEMP_HEIGHT) { // Reached bottom or dead
			blitAsteroid(asteroid, ERASE);

			asteroid->active = 0;
		} else {
			if (xMoved || yMoved) {
				blitAsteroid(asteroid, ERASE);
				blitAsteroid(asteroid, DRAW);
			}
		}
	}
}


/* ----------- UFOS ---------- */
static ufo_t ufoArray[MAX_UFOS] = {0};

void addUfo() {
	for (uint8_t i = 0; i < MAX_UFOS; i++) {
		ufo_t *ufo = &ufoArray[i];


		if (!ufo->active) {
			uint8_t randType = (uint8_t)randomRange(0, 4);

			ufo->active = 1;
			ufo->x = (int16_t)randomRange(1 << 6, TEMP_WIDTH << 6); // Spawn within 1 -> width
			ufo->y = 0;
			ufo->vX = 0;
			ufo->vY = (int16_t)randomRange(1 << 3, 0x40); // Fastest speed is 1/16, slowest is 1/32 cells per frame.
			ufo->type = randType;
			ufo->shotDelay = (randType + 1) << 4; // Aggressiveness based of type

			break; // Stop looking for empty spot, as we have added the ufo
		}
	}
}


void updateUfos() {
	for (uint8_t i = 0; i < MAX_UFOS; i++) {
		ufo_t *ufo = &ufoArray[i];


		if (!ufo->active) continue; // Skip non-active UFOS

		int16_t oldXCell = ufo->x >> 6;
		int16_t oldYCell = ufo->y >> 6;

		uint8_t xMoved = oldXCell != ((ufo->x += ufo->vX) >> 6);
		uint8_t yMoved = oldYCell  != ((ufo->y += ufo->vY) >> 6);

		if ((ufo->y >> 6) >= TEMP_HEIGHT) { // Reached bottom or dead
			blitUfo(ufo, ERASE);

			ufo->active = 0;
		} else {
			if (xMoved || yMoved) {
				blitUfo(ufo, ERASE);
				blitUfo(ufo, DRAW);
			}
			ufo->shotDelay--;
			if (ufo->shotDelay == 0) {
				addBullet(ufo->x + ((int16_t)1 << 6), ufo->y + ((int16_t)2 << 6), ufo->vY);

				ufo->shotDelay = (ufo->type + 1) << 4;
			}
		}
	}
}


/* ----------- BULLETS ---------- */
static bullet_t bulletArray[MAX_BULLETS] = {0};


// VERY SIMPLE: SHOULD BE CHANGED
void addBullet(int16_t x, int16_t y, int16_t vY) {
	for (uint8_t i = 0; i < MAX_BULLETS; i++) {
		bullet_t *bullet = &bulletArray[i];

		if (!bullet->active) {
			vY &= 0x8000; // make bullet move 2 cells in speed based on direction vY is in;
			vY +=2 << 6;

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

		if (!bullet->active) continue;

		int16_t oldXCell = bullet->x >> 6;
		int16_t oldYCell = bullet->y >> 6;

		uint8_t xMoved = oldXCell != ((bullet->x += bullet->vX) >> 6);
		uint8_t yMoved = oldYCell  != ((bullet->y += bullet->vY) >> 6);

		if ((bullet->y >> 6) >= TEMP_HEIGHT) { // Reached bottom or dead
			blitBullet(bullet, ERASE);

			bullet->active = 0;
		} else {
			if (xMoved || yMoved) {
				blitBullet(bullet, ERASE);
				blitBullet(bullet, DRAW);
			}
		}
	}
}
