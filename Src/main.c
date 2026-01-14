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

	spaceship_t ship;
	ship.x = 10;
	ship.y = 10;
	ship.lvl = 0;

	drawSpaceship(&ship);

    while (1) {}
}
