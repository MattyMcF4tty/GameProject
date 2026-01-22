#include "main.h"

static void initBoard()
{
	uart_init(230400); // Set UART

	LEDinitializer(); // Init LED
	enableJoystick(); // Init Joystick
	timerInit();	  // Init timer

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
	gameConfig.winStartX = 1;
	gameConfig.winStartY = 8;

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
		screen_t prevScreen = NO_SCREEN;
		active_button_t button = NONE;
		gameState.highScore = 0;
		joystick_input_t joyInput;
		timerStart(); // Start timer
		while (1)
		{
			readJoystick(&joyInput);

			// Allow for boss key click out of tick rate
			if (joyInput.button == BTN_RED)
			{ // Read boss key

				bossKey(); // Show boss screen
				gameState.bossModeActive = 1;

				while (gameState.bossModeActive)
				{
					// listen for boss key click
					readJoystick(&joyInput);
					gameState.bossModeActive = joyInput.button != BTN_RED;
				}

				clearScreen();
			}

			// Only update game on clock tick
			else if (timerTickOccurred())
			{

				switch(gameState.screen) {

					case (GAME):
						if (prevScreen != GAME) {
							 drawBordersMenu(gameConfig.winStartX, gameConfig.winStartY, gameConfig.winW, gameConfig.winH);
							 prevScreen = GAME;
						}

						updateGameState(&gameConfig, &gameState, &joyInput); // Handle next frame

						updateScore(&gameState.score); // Give points for time alive
						// drawHud(&gameState);
						updateLCD(&gameState);	   // Update LCD
						LEDLives(gameState.lives); // Update LED
						break;

					case (MENU):
						if (prevScreen != MENU) {
							DrawMenuBorderAndTitle(&gameConfig);
							MenuButtons(&gameConfig);
							prevScreen = MENU;
						}

						navigator(&gameState.screen, joyInput.xAxis,
									joyInput.button == BTN_WHITE, &button);

						break;

					case (HELP):
						drawHelpScreen(&gameConfig);

						while (joyInput.button != BTN_WHITE) {
							readJoystick(&joyInput);
						}
						gameState.screen = MENU;
						break;

					case (GAME_OVER):
						// Draw death screen
						drawDeathScreen(&gameConfig, &gameState);
						while (1)
						{
							readJoystick(&joyInput);
							// Update button select

							if (gameState.screen == GAME_OVER)
							{
								// TEMP
								initGameState(&gameConfig, &gameState);
							}
						}
						break;

					default:
						gameState.screen = MENU; // Fallback
						break;
				}
			}
		}
	}

	// Impossible, but at least they now know
	clearScreen();
	goHome();
	printf("Something went wrong restart game");

	// Make terminal run indefinitely
	while (1) {}
}
