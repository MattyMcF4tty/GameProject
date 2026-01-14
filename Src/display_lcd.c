#include "display_lcd.h"

// Returns a pointer to buffer in charset LUT.
// Also sets the pointer to constant preventing accidental changes.
const uint8_t *charToBuffer(char c) {

	// Clamp char to be between 0x20 and 0x7E
    if 		(c < 0x20 ) c = 0x20;
    else if (c > 0x7E)	c = 0x7E;

	return character_data[c-0x20];
}

