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
		#define SPR_W 7 // REMEMBER TO UPDATE IN RENDER.C

		extern const uint8_t shipLevelSprites[4][SPR_H][SPR_W]; 	// Ship level sprite LUT
		extern const uint8_t shipPowerUpSprites[4][SPR_H][SPR_W];	// Ship power up LUT

#endif
