#ifndef _GAME_MASTER_H_
#define _GAME_MASTER_H_

	/* ----- Dependencies ----- */
	#include <stdint.h>
	#include <stdlib.h>

	/* ----- Config ----- */
	#define MAX_ASTEROIDS	20
	#define MAX_UFOS		40
	#define MAX_BULLETS		100

	/* ----- Type definitions ----- */
	typedef struct {
		uint8_t lives;
		uint32_t score;
		uint32_t highScore;
		uint8_t level;
		uint8_t spawnRate;
	} gameState_t;

	typedef struct {
		uint8_t x, y;
		int32_t vX, vY; // 16.16
		uint8_t lvl;
		uint8_t powerUp;
	} spaceship_t;

	typedef struct {
		uint8_t active;
		uint8_t x, y;
		int32_t vX, vY; // 16.16
		uint8_t dmg;
		uint8_t type;
	} bullet_t;

	typedef struct {
		uint8_t active;
		uint8_t x, y;
		int32_t vX, vY; // 16.16
		uint8_t lives;
		uint8_t type;
	} asteroid_t;

	typedef struct {
		uint8_t active;
		uint8_t x, y;
		int32_t vX, vY; // 16.16
		uint8_t lives;
		uint8_t type;
		uint8_t shotDelay; // Number of ticks before alien shoots again
	} ufo_t;


	/* ----- Functions ----- */
	void addAsteroid();
	void updateAsteroids();

	void addUfo();
	void updateUfos();

	void addBullet(uint8_t x, uint8_t y, uint32_t vY);
	void updateBullets();

#endif
