#ifndef JOYSTICK30010_H_
#define JOYSTICK30010_H_

#include "30010_io.h" // Input/output library for this course
#include "stm32f30x_conf.h" // STM32 config
#include "stdint.h"
#include "stdio.h"

void enableJoystick();
void enableGpioClock();
void enablePots();
void enableButtons();

int8_t readPotXaxis(void);
int8_t readPotYaxis(void);

int16_t readButton(int8_t pin);

#endif /* JOYSTICK30010_H_ */
