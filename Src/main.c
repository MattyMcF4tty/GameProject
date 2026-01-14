#include "main.h"

static void initBoard() {
	uart_init(9600); // Set UART

	/* ---- Enable necessary GPIO's ----- */
	gpioEnable(GPIOA);	// Joystick,
	gpioEnable(GPIOB);	// Joystick,
	gpioEnable(GPIOC);	// Joystick,

	return;
}

int main() {
    initBoard(); // Should always be first

	clearScreen();
	goHome();

    while (1) {}
}
