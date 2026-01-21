#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include "30010_io.h"
#include "charset.h"
#include "timer.h"
#include <string.h>
#include <stdio.h>
#include "charset.h"

void lcdTextInit(void);
void lcdWriteString(const char *str, uint16_t slice, uint8_t line);
void lcdUpdate(void);
static uint8_t lcd_buffer[512];

#endif
