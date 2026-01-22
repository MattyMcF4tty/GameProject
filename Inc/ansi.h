#ifndef _ANSI_H_
#define _ANSI_H_

	/* ----- Dependencies ----- */
	#include <stdint.h>
	#include <stdio.h>

	/* ----- Functions ----- */
	void goHome();
	void clearScreen();
	void clearLine(uint8_t y);
	void goTo(uint8_t x, uint8_t y);
	void goToCoords(int16_t x, int16_t y);
	void fgColor(uint8_t foreground);
	void bgColor(uint8_t background);
	void resetBgColor();
	void blink(uint8_t on);
	void bold(uint8_t on);
	void up();
	void down();

#endif
