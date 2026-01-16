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
		#define SHIP_H 4 // REMEMBER TO UPDATE IN RENDER.C
		#define SHIP_W 7 // REMEMBER TO UPDATE IN RENDER.C

		extern const uint8_t shipLevelSprites[4][SHIP_H][SHIP_W]; 	// Ship level sprite LUT
		extern const uint8_t shipPowerUpSprites[4][SHIP_H][SHIP_W];	// Ship power up LUT

		/* ----- ASTROID ----- */
		#define AST_H 6 // REMEMBER TO UPDATE IN RENDER.C
		#define AST_W 8 // REMEMBER TO UPDATE IN RENDER.C

		extern const uint8_t asteroidSprites[2][AST_H][AST_W];

		/* ----- UFO ----- */
		#define UFO_H 2 // REMEMBER TO UPDATE IN RENDER.C
		#define UFO_W 3 // REMEMBER TO UPDATE IN RENDER.C

		extern const uint8_t ufoSprites[5][UFO_H][UFO_W];


#endif
