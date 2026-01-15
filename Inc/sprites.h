#ifndef _SPRITES_H_
#define _SPRITES_H_

	/* ----- Dependencies ----- */
	#include <stdint.h>
	#include <stdio.h>
	#include "ansi.h"

	/* ----- Type definitions ----- */
	typedef struct {
		uint8_t offset;
		uint8_t color;
	} pixel_t;

	/* ----- Sprites ----- */

		/* ----- SPACESHIP ----- */
		#define SPR_H 4 // REMEMBER TO UPDATE IN RENDER.C
		#define SPR_W 5 // REMEMBER TO UPDATE IN RENDER.C
		const uint8_t defaultShip[SPR_H][SPR_W];


#endif
