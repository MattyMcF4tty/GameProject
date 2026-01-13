#include "display_lcd.h"

const char *charToBuffer(char c)
{
	c -= 0x20;
    if 		(c < 0x20 ) c = 0x20;
    else if (c > 0x7E)	c = 0x7E;

    return character_data[(uint8_t)c];
}
