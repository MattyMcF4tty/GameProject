/*
 * hud.h
 *
 *  Created on: 16 Jan 2026
 *      Author: oscar
 */



#ifndef _HUD_H_
#define _HUD_H_

	/* ----- Dependencies ----- */
	#include <stdint.h>
	#include <stdio.h>
	#include "stm32f30x_conf.h"
	#include "game_master.h"

	/* ----- Functions ----- */
	void drawHud(const gameState_t *state);
	void hudLoseLife(void);
	uint8_t hudGetLives(void);
	void updateScore(uint32_t *score);
	uint16_t hudGetScore(void);


#endif
