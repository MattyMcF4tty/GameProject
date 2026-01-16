#ifndef _GAME_MASTER_H_
#define _GAME_MASTER_H_


	/*
	 * Why use int16 for position?
	 * We use a 10.6 fixed int16 for the x and y axis
	 * This is to both save on data as the precesion of int32 is not needed.
	 * with the 10.6 fixed point int16 the range is −512.0 to +511.984375.
	 * Which is plenty as most screen terminals is ~200 cells wide, at fullscreen.
	 *
	 * We also allow for x and y to be negative only because we will clamp the values later in our code.
	 * And having both velocity and the position in the same type makes calculations easier.
	 */

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
		int16_t x, y; 	// Q10.6 Fixed point
		int16_t vX, vY; // Q10.6 Fixed point
		uint8_t lvl;
		uint8_t powerUp;
	} spaceship_t;

	typedef struct {
		uint8_t active;
		int16_t x, y; 	// Q10.6 Fixed point
		int16_t vX, vY; // Q10.6 Fixed point
		uint8_t dmg;
		uint8_t type;
	} bullet_t;

	typedef struct {
		uint8_t active;
		int16_t x, y; 	// Q10.6 Fixed point
		int16_t vX, vY; // Q10.6 Fixed point
		uint8_t lives;
		uint8_t type;
	} asteroid_t;

	typedef struct {
		uint8_t active;
		int16_t x, y; 	// Q10.6 Fixed point
		int16_t vX, vY; // Q10.6 Fixed point
		uint8_t lives;
		uint8_t type;
		uint8_t shotDelay; // Number of ticks before alien shoots again
	} ufo_t;


	/* ----- Functions ----- */
	void addAsteroid();
	void updateAsteroids();

	void addUfo();
	void updateUfos();

	void addBullet(int16_t x, int16_t y, int16_t vY);
	void updateBullets();

#endif
