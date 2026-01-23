/*
 * LCD.c
 *
 *  Created on: 19. jan. 2026
 *      Author: tobia
 */

#include "LCD.h""

static uint8_t lcd_buffer[512];

void lcdTextInit(void)
{
    lcd_init();

    for (uint16_t i = 0; i < sizeof(lcd_buffer); i++) //Reset buffer
    {
        lcd_buffer[i] = 0;
    }

    lcd_push_buffer(lcd_buffer);
}


void lcdWriteString(const char *str, uint16_t slice, uint8_t line)
{
    uint16_t line_start = line * 128;
    uint16_t pixel = 0;

    uint16_t char_skip = slice / 6;   //determines how many full characters to skip
    uint8_t  col_skip  = slice % 6;   // determines how many pixels of the first character to skip

    str += char_skip; //moves the string pointer forward

    while (*str && pixel < 128) // loops until either \0 or the horizontal limit is reached
    {
        char c = *str++; //handles the current character of the string and afterwards it moves on to the next character

        if (c < 0x20 || c > 0x7F) //ensures that the LCD only is provided the desired characters
            c = 0x20;

        // Draw character columns
        // uint8_t i = col_skip enables it to render partial characters
        for (uint8_t i = col_skip; i < 5 && pixel < 128; i++)
        {
            lcd_buffer[line_start + pixel] =
                character_data[c - 0x20][i];
            pixel++;
        }

        // Space between characters
        if (pixel < 128)
        {
            lcd_buffer[line_start + pixel] = 0x00;
            pixel++; //moves the horizontal drawing cursor 1 pixel to the right
        }

        col_skip = 0;  // Only applies to the first character
    }

    lcd_push_buffer(lcd_buffer);
}

void updateLCD(const gameState_t *gameState)
{
	char text[32];

	for (uint16_t i = 0; i < sizeof(lcd_buffer); i++) //Reset buffer
	{
	    lcd_buffer[i] = 0;
	}

	snprintf(text, sizeof(text), "Lives: %d", gameState->lives);
	lcdWriteString(text, 0, 1);

	snprintf(text, sizeof(text), "Score: %lu", gameState->score);
	lcdWriteString(text, 0, 2);

	lcd_push_buffer(lcd_buffer);
}


