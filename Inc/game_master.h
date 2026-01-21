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
    #include "joystick30010.h"


	/* ----- Type definitions ----- */
	typedef struct {
		int16_t x, y; 	// Q10.6 Fixed point
		int16_t vX, vY; // Q10.6 Fixed point
		uint8_t lvl;
		uint8_t shotAngle;
		uint8_t powerUp;
		uint8_t shot_Angle;
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
		int16_t gravity;
	} asteroid_t;

	typedef struct {
		uint8_t active;
		int16_t x, y; 	// Q10.6 Fixed point
		int16_t vX, vY; // Q10.6 Fixed point
		uint8_t lives;
		uint8_t type;
		uint8_t shotDelay; // Number of ticks before alien shoots again
	} ufo_t;

	typedef struct {
		uint8_t active;
		int16_t x, y; 	// Q10.6 Fixed point
		int16_t vX, vY; // Q10.6 Fixed point
		uint8_t type;
	} power_up_t;

	typedef struct {
		uint8_t maxBullets;
		uint8_t maxUfos;
		uint8_t maxAsteroids;
		uint8_t maxPowerUps;
		uint8_t difficulty;		// Difficulty multiplier
		uint8_t winW;			// Window width
		uint8_t winH;			// Window height
	} gameConfig_t;

	typedef struct {
		uint8_t 	lives;
		uint32_t	score;
		uint32_t 	highScore;
		uint8_t 	level;
		uint8_t 	spawnRate;
		ufo_t 		*ufoArray;
		asteroid_t 	*asteroidArray;
		bullet_t 	*bulletArray;
		power_up_t 	*powerUpArray;
		spaceship_t *ship;
	} gameState_t;


	/* ----- Functions ----- */
	uint8_t initGameState(const gameConfig_t *config, gameState_t *state);
	void updateGameState(const gameConfig_t *config, gameState_t *state);

	void addSpaceship(spaceship_t *ship, int16_t startX, int16_t startY);
	void updateSpaceship(const gameConfig_t *config, spaceship_t *ship, bullet_t *bulletArray);
	void updateSpaceshipShotAngle(spaceship_t *ship);

#endif
