#include "sprites.h"
#include "ansi.h"


/* ---------- ASTEROID ---------- */
const uint8_t asteroidSprites[SPRITE_AST_TYPES][SPRITE_AST_H][SPRITE_AST_W] = {
		{		// TYPE 0
			    {0, 0, 0, 7, 7, 7, 0, 0},
			    {0, 7, 7, 7, 7, 7, 7, 0},
			    {7, 7, 7, 7, 7, 7, 7, 7},
				{7, 7, 7, 7, 7, 7, 7, 7},
				{0, 7, 7, 7, 7, 7, 7, 0},
				{0, 0, 7, 7, 7, 0, 0, 0},
		},
		{		// TYPE 1
			    {0, 0, 0, 0, 0, 0, 0, 0},
			    {0, 0, 0, 6, 0, 0, 0, 0},
			    {0, 0, 6, 3, 7, 0, 0, 0},
				{0, 6, 0, 7, 3, 7, 0, 6},
				{0, 0, 0, 0, 7, 3, 6, 0},
				{0, 0, 0, 0, 0, 6, 0, 0},
		},
};

/* ---------- SPACESHIP ---------- */
const uint8_t shipLevelSprites[SPRITE_SHIP_LEVELS][SPRITE_SHIP_H][SPRITE_SHIP_W] = {
		{		// LEVEL 0
			    {0, 0, 0, 1, 0, 0, 0},
			    {0, 0, 1, 6, 1, 0, 0},
			    {0, 1, 1, 1, 1, 1, 0},
			    {0, 0, 3, 0, 3, 0, 0}
		},
		{		// LEVEL 1
			    {0, 0, 0, 1, 0, 0, 0},
			    {7, 0, 1, 6, 1, 0, 7},
			    {1, 1, 1, 1, 1, 1, 1},
			    {0, 0, 3, 0, 3, 0, 0}
		},
		{		// LEVEL 2
			    {0, 0, 0, 7, 0, 0, 0},
			    {7, 0, 1, 6, 1, 0, 7},
			    {1, 1, 1, 1, 1, 1, 1},
			    {0, 0, 3, 0, 3, 0, 0}
		},
		{		// LEVEL 3 MAX LEVEL
			    {0, 0, 0, 7, 0, 0, 0},
			    {7, 0, 3, 6, 3, 0, 7},
			    {3, 3, 3, 3, 3, 3, 3},
			    {0, 0, 5, 0, 5, 0, 0}
		},
};

const uint8_t shipPowerUpSprites[SPRITE_SHIP_POWER_UPS][SPRITE_SHIP_H][SPRITE_SHIP_W] = {
		{		// POWER UP 1: MORE DAMAGE
			    {0, 0, 0, 0, 0, 0, 0},
			    {7, 0, 0, 0, 0, 0, 7},
			    {7, 0, 0, 0, 0, 0, 7},
			    {0, 0, 0, 0, 0, 0, 0}
		},
		{		// POWER UP 2: MORE SPEED
			    {0, 0, 0, 0, 0, 0, 0},
			    {0, 0, 0, 0, 0, 0, 0},
			    {0, 0, 0, 0, 0, 0, 0},
			    {3, 0, 3, 0, 3, 0, 3}
		},
};

/* ---------- UFO ---------- */
const uint8_t ufoSprites[SPRITE_UFO_TYPES][SPRITE_UFO_H][SPRITE_UFO_W] = {
		{		// TYPE 0
			    {0, 6, 0},
			    {1, 1, 1},
		},
		{		// TYPE 1
			    {0, 6, 0},
			    {2, 2, 2},
		},
		{		// TYPE 2
			    {0, 6, 0},
			    {3, 3, 3},
		},
		{		// TYPE 3
			    {0, 6, 0},
			    {5, 5, 5},
		},
		{		// TYPE 4
			    {0, 6, 0},
			    {4, 4, 4},
		},
};


/* ---------- POWERUP ---------- */
const char powerUpSpritesChar[SPRITE_POWER_UP_TYPES][SPRITE_POWER_UP_H][SPRITE_POWER_UP_W] = {
		{
				{ '/', ' ' },
				{ '-', '-' },
				{ ' ', '/' },
		},
		{
				{ ' ', '^' },
				{ ' ', '#' },
				{ ' ', '#' },
		},
};

const uint8_t powerUpSpritesColor[SPRITE_POWER_UP_TYPES][SPRITE_POWER_UP_H][SPRITE_POWER_UP_W] = {
		{
				{ 3, 0 },
				{ 3, 3 },
				{ 0, 3 },
		},
		{
				{ 0, 1 },
				{ 0, 7 },
				{ 0, 7 },
		},
};

