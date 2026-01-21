#ifndef _SPRITES_H_
#define _SPRITES_H_

	/* ----- Dependencies ----- */
	#include <stdint.h>
	#include <stdio.h>

	/* ----- Type definitions ----- */
	typedef struct {
		uint8_t offset;
		uint8_t color;
	} pixel_t;

	/* ----- Sprites ----- */

		/* ----- ASTROID ----- */
		#define SPRITE_AST_TYPES 2
		#define SPRITE_AST_H 6
		#define SPRITE_AST_W 8

		extern const uint8_t asteroidSprites[SPRITE_AST_TYPES][SPRITE_AST_H][SPRITE_AST_W];

		/* ----- SPACESHIP ----- */
		#define SPRITE_SHIP_LEVELS 4
		#define SPRITE_SHIP_POWER_UPS 2
		#define SPRITE_SHIP_H 4
		#define SPRITE_SHIP_W 7

		extern const uint8_t shipLevelSprites[SPRITE_SHIP_LEVELS][SPRITE_SHIP_H][SPRITE_SHIP_W]; 	// Ship level sprite LUT
		extern const uint8_t shipPowerUpSprites[SPRITE_SHIP_POWER_UPS][SPRITE_SHIP_H][SPRITE_SHIP_W];	// Ship power up LUT

		/* ----- UFO ----- */
		#define SPRITE_UFO_TYPES 5
		#define SPRITE_UFO_H 2
		#define SPRITE_UFO_W 3

		extern const uint8_t ufoSprites[SPRITE_UFO_TYPES][SPRITE_UFO_H][SPRITE_UFO_W];

		/* ----- POWERUP ----- */
		#define SPRITE_POWER_UP_TYPES 2
		#define SPRITE_POWER_UP_H 3
		#define SPRITE_POWER_UP_W 2

		extern const char powerUpSpritesChar[SPRITE_POWER_UP_TYPES][SPRITE_POWER_UP_H][SPRITE_POWER_UP_W];
		extern const uint8_t powerUpSpritesColor[SPRITE_POWER_UP_TYPES][SPRITE_POWER_UP_H][SPRITE_POWER_UP_W];
#endif
