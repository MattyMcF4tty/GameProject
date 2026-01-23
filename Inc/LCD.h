#ifndef _LCD_H
#define _LCD_H

	/* ----- Dependencies ----- */
	#include <stdint.h>
	#include "30010_io.h"
	#include "charset.h"
	#include "timer.h"
	#include "game_master.h"
	#include <stdio.h>

	/* ----- Functions ----- */
	void lcdTextInit(void);
	void lcdWriteString(const char *str, uint16_t slice, uint8_t line);
	void updateLCD(const gameState_t *gameState);

#endif
