#include "main.h"

static void initBoard()
{
	uart_init(230400); // Set UART

	LEDinitializer(); // Init LED
	enableJoystick(); // Init Joystick
	initRandom();	  // Init random, MUST BE BELOW enableJoystick();
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


	uint8_t initError = 0;
	gameState.screen = MENU;
	screen_t prevScreen = NO_SCREEN;
	joystick_btn_t prevButton = BTN_NONE;
	active_button_t button = NONE;
	gameState.highScore = 0;
	joystick_input_t joyInput;
	timerStart(); // Start timer

	initError = initGameState(&gameConfig, &gameState);

	while (!initError)
	{
	    readJoystick(&joyInput);

	    goHome();

	    printf("%d", joyInput.button);

	    if (joyInput.button == BTN_RED)
	    {
	        bossKey();
	        gameState.bossModeActive = 1;

	        while (gameState.bossModeActive)
	        {
	            readJoystick(&joyInput);
	            // exit on RED press (edge detect inside loop)
	            static joystick_btn_t last = BTN_NONE;   // if you refuse static, do a local prev in this loop
	            joystick_btn_t e = (joyInput.button != last) ? joyInput.button : BTN_NONE;
	            last = joyInput.button;

	            if (e == BTN_RED) gameState.bossModeActive = 0;
	        }
	        clearScreen();
	    }
	    else if (timerTickOccurred())
	    {
	    	if (gameState.screen == GAME)
				{

					if (prevScreen != GAME)
					{
						clearScreen();
						prevScreen = GAME;
						gameState.lives = 3;
						gameState.level = 0;
						gameState.score = 0;

						drawBordersMenu(gameConfig.winStartX, gameConfig.winStartY,
										gameConfig.winW, gameConfig.winH);
					}

					updateGameState(&gameConfig, &gameState, &joyInput);
					updateScore(&gameState.score);
					drawHud(&gameConfig, &gameState);
					updateLCD(&gameState);
					LEDLives(gameState.lives);
				}
	        else
	        {
	            if (gameState.screen != prevScreen || prevButton == BTN_RED)
	            {
	                clearScreen();
	                prevScreen = gameState.screen;

	                switch (gameState.screen)
	                {
	                    case MENU:
	                    	DrawMenuBorderAndTitle(&gameConfig);
	                    	MenuButtons(&gameConfig);
	                    	break;
	                    case HELP:
	                    	drawHelpScreen(&gameConfig);
	                    	break;
	                    case GAME_OVER:
	                    	drawDeathScreen(&gameConfig, &gameState);
	                    	break;
	                    default:
	                    	gameState.screen = MENU;
	                    	break;
	                }
	            }

	            navigator(&gameState.screen, joyInput.xAxis, joyInput.button, &button);
	        }
	    }

	    prevButton = joyInput.button;  // CRITICAL
	}


	// Ram allocation error. Crash game and tell player
	resetBgColor();
	clearScreen();
	goHome();
	fgColor(1);
	bold(1);
	printf("It was not possible to allocate the needed amount of RAM based of your settings.\n");
	printf("Please restart game and lower your settings or if possible allocate more RAM.");

	// Make terminal run indefinitely
	while (1) {}
}
