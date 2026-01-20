#ifndef _RENDER_H_
#define _RENDER_H_


	/* ----- Dependencies ----- */
	#include <stdint.h>
	#include <stdio.h>
	#include "sprites.h"
	#include "game_master.h"

 	/* ----- Type definitions ----- */
	typedef enum {
		DRAW,
		ERASE
	} blitMode_t;

	/* ----- Functions ----- */
	void blitAsteroid(const asteroid_t *asteroid, blitMode_t mode);
	void blitSpaceship(const spaceship_t *ship, blitMode_t mode);
	void blitUfo(const ufo_t *ufo, blitMode_t mode);
	void blitBullet(const bullet_t *bullet, blitMode_t mode);

#endif
