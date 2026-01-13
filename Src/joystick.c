#include "joystick.h"

uint8_t joystickEnabled = 1;

uint8_t readJoystick() {
    uint8_t state = 0; // One hot state

	if (joystickEnabled) {
	    uint16_t up     = gpioReadPin(GPIOA, 4); // PA4
	    uint16_t down   = gpioReadPin(GPIOB, 0); // PB0
	    uint16_t left   = gpioReadPin(GPIOC, 1); // PC1
	    uint16_t right  = gpioReadPin(GPIOC, 0); // PC0
	    uint16_t center = gpioReadPin(GPIOB, 5); // PB5

	    if      (up)     state = (1 << 0);  // 00001
	    else if (down)   state = (1 << 1);  // 00010
	    else if (left)   state = (1 << 2);  // 00100
	    else if (right)  state = (1 << 3);  // 01000
	    else if (center) state = (1 << 4);  // 10000
	}

    return state;
}

void toggleJoystick(uint8_t toggle) {
	joystickEnabled = toggle >= 1 ? 1 : 0; // cap value at one
	return;
}
