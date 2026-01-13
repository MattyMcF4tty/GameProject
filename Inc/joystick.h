#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

	/* ----- Dependencies ----- */
	#include "stm32_helpers.h"


	/* ----- Functions ----- */
	uint8_t readJoystick(); // Reads the joystick position and returns a onehot 5 bit bus
	void toggleJoystick(uint8_t toggle); // Enable/disable game joystick input

#endif
