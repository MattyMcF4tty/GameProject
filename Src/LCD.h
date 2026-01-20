#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include "30010_io.h"
#include "charset.h"
#include "timer.h"
#include <string.h>
#include <stdio.h>
#include "charset.h"

void lcd_text_init(void);
void lcd_write_string(const char *str, uint16_t slice, uint8_t line);
void lcd_update(void);

#endif
