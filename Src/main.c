#include "main.h"

static void initBoard() {
	uart_init(115200); // Set UART

	/* ---- Enable necessary GPIO's ----- */
	gpioEnable(GPIOA);	// Joystick,
	gpioEnable(GPIOB);	// Joystick,
	gpioEnable(GPIOC);	// Joystick,

	enableJoystick();
	return;
}

int main() {
    initBoard(); // Should always be first

    srand(122);   // Init randomness

    resetBgColor();
	clearScreen();
	goHome();

	// settings
	gameConfig_t gameConfig;
	gameConfig.maxBullets = 100;
	gameConfig.maxAsteroids = 20;
	gameConfig.maxUfos = 40;
	gameConfig.difficulty = 1;
	gameConfig.winH = 50;
	gameConfig.winW = 200;

	gameState_t gameState;

	uint8_t initError = initGameState(&gameConfig, &gameState);
	if (initError) {
		// Error message

		printf("It was not possible to allocate the needed amount of RAM based of your settings.\n");
		printf("Please lower your settings or if possible allocate more RAM.");
	}
	else {
		// Game started correctly

	    while (1) {
	    	updateGameState(&gameConfig, &gameState);
	    }
	}

	// Make terminal run indefinently
    while (1) {}
}
