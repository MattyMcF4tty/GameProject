#include "main.h"

static void initBoard()
{
	uart_init(230400); // Set UART

	LEDinitializer();	// Init LED
	enableJoystick();	// Init Joystick
	timerInit();		// Init timer

	__enable_irq();
	return;
}

int main()
{
	initBoard(); // Should always be first

	resetBgColor();
	clearScreen();
	goHome();


	// settings
	gameConfig_t gameConfig;
	gameConfig.maxBullets = 100;
	gameConfig.maxAsteroids = 5;
	gameConfig.maxUfos = 40;
	gameConfig.maxPowerUps = 5;
	gameConfig.difficulty = 1;
	gameConfig.winH = 64;
	gameConfig.winW = 207;


	gameState_t gameState;

	uint8_t initError = initGameState(&gameConfig, &gameState);
	if (initError)
	{
		// Error message
		printf("It was not possible to allocate the needed amount of RAM based of your settings.\n");
		printf("Please restart game and lower your settings or if possible allocate more RAM.");
	}
	else
	{
		joystick_input_t joyInput;
		joystick_input_t prevJoyInput;
		timerStart(); // Start timer
		while (1)
		{

			 // Read joystick values

			// Allow for boss key click out of tick rate
			if (joyInput.button == BTN_RED) { // Read boss key

				bossKey(); // Show boss screen
				gameState.bossModeActive = 1;

				while(gameState.bossModeActive) {
					// listen for boss key click
					readJoystick(&joyInput, &prevJoyInput);
					gameState.bossModeActive = !joyInput.button == BTN_RED;
				}
			}

			// Only update game on clock tick
			else if (timerTickOccurred()) {
				readJoystick(&joyInput, &prevJoyInput);

				if (gameState.gameMode == MENU)
				{
					// Draw menu
					printf("start");
					while(1) {
						readJoystick(&joyInput, &prevJoyInput);
						// Update button select
					}

				}
				else if (gameState.gameMode == GAME)
				{
					updateGameState(&gameConfig, &gameState, &joyInput);	// Handle next frame

					updateScore(&gameState.score);				// Give points for time alive
					//drawHud(&gameState);
					updateLCD(&gameState);						// Update LCD
					LEDLives(gameState.lives);					// Update LED
				}
				else if (gameState.gameMode == GAME_OVER)
				{
					// Draw death screen
					printf("dead");
					while(1) {
						readJoystick(&joyInput, &prevJoyInput);
						// Update button select

						if (joyInput.xAxis != JOY_X_NONE) {
							//TEMP
							initGameState(&gameConfig, &gameState);
						}
					}
				}
			}
		}
	}


	// Impossible, but at least they now know
	clearScreen();
	goHome();
	printf("Something went wrong restart game");

	// Make terminal run indefinitely
	while (1)
	{}
}
