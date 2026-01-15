#include "main.h"

static void initBoard() {
	uart_init(115200); // Set UART

	/* ---- Enable necessary GPIO's ----- */
	gpioEnable(GPIOA);	// Joystick,
	gpioEnable(GPIOB);	// Joystick,
	gpioEnable(GPIOC);	// Joystick,

	return;
}

int main() {
    initBoard(); // Should always be first

    srand(1231);   // Init randomness

    resetBgColor();
	clearScreen();
	goHome();


    while (1) {


    }
}
