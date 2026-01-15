#ifndef _GAME_MASTER_H_
#define _GAME_MASTER_H_

	/* ----- Dependencies ----- */
	#include <stdint.h>



	/* ----- Type definitions ----- */
	typedef struct {
		uint8_t lives;
		uint32_t score;
		uint32_t highScore;
		uint8_t level;
	} gameState_t;

	typedef struct {
		uint8_t x, y;
		int32_t vX, vY; // 16.16
		uint8_t lvl;
		uint8_t powerUp;
	} spaceship_t;

	typedef struct {
		uint8_t x, y;
		int32_t vX, vY; // 16.16
		uint8_t dmg;
		uint8_t type;
	} bullet_t;

	typedef struct {
		uint8_t x, y;
		int32_t vX, vY; // 16.16
		uint8_t lives;
		uint8_t type;
	} asteroid_t;

	typedef struct {
		uint8_t x, y;
		int32_t vX, vY; // 16.16
		uint8_t lives;
		uint8_t type;
	} ufo_t;

	/* ----- Functions ----- */


#endif
