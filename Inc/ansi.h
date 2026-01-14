#ifndef _ANSI_H_
#define _ANSI_H_

	/* ----- Dependencies ----- */
	#include <stdint.h>

	/* ----- Functions ----- */
	void goHome();
	void clearScreen();
	void clearLine(uint8_t y);
	void goTo(uint8_t x, uint8_t y);
	void fgColor(uint8_t foreground);
	void bgColor(uint8_t background);
	void resetBgColor();

#endif
