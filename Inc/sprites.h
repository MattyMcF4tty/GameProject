#ifndef _SPRITES_H_
#define _SPRITES_H_

	/* ----- Dependencies ----- */
	#include <stdint.h>
	#include <stdio.h>
	#include "ansi.h"

	/* ----- Type definitions ----- */
	typedef struct {
		uint8_t x, y;
		int32_t vX, vY; // 16.16
		uint8_t lvl;
		uint8_t powerUp;
	} spaceship_t;

	typedef struct {
		uint8_t offset;
		uint8_t color;
	} pixel_t;

	/* ----- Functions ----- */
	void drawSpaceship(const spaceship_t *ship);


#endif
