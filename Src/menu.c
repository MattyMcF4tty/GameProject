#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"		// Input/output library for this course
#include "menu.h"
#include "ansi.h"
#include "game_master.h"


void DrawTitleScreen(uint8_t startX, uint8_t startY) //(70,10)
{
	fgColor(6);

	const char *titleScreen[] = {
		" ____                         ____  _                                                    _",
		"/ ___| _ __   __ _  ___ ___  |  _ \\(_)___  __ _  __ _ _ __ ___  ___ _ __ ___   ___ _ __ | |_",
		"\\___ \\| '_ \\ / _` |/ __/ _ \\ | | | | / __|/ _` |/ _` | '__/ _ \\/ _ \\ '_ ` _ \\ / _ \\ '_ \\| __|",
		" ___) | |_) | (_| | (_|  __/ | |_| | \\__ \\ (_| | (_| | | |  __/  __/ | | | | |  __/ | | | |_ ",
		"|____/| .__/ \\__,_|\\___\\___| |____/|_|___/\\__,_|\\__, |_|  \\___|\\___|_| |_| |_|\\___|_| |_|\\__|",
		"      |_|                                       |___/",
		"              "

	};

	const uint8_t nLines = sizeof(titleScreen) / sizeof(titleScreen[0]);

	for (uint8_t i = 0; i < nLines; i++)
	{
	    goTo(startX, startY + i);
	    printf("%s\r\n", titleScreen[i]);
	}
	resetBgColor();
}

void drawBordersMenu(uint8_t winStartX, uint8_t winStartY, uint8_t winW, uint8_t winH)
{

	fgColor(7);
	char ASCII_character_top = 205;
	char ASCII_character_sides = 186;

	goTo(winStartX, winStartY); /*Toppen*/
	printf("%c", 201);
	for (uint8_t x = winStartX + 1; x < winW; x++)
	{
		printf("%c", ASCII_character_top);
	}
	printf("%c", 187);

	for (uint8_t y = winStartY + 1; y < winH; y++)
	{ /* Siderne  */
		goTo(winStartX, y);
		printf("%c", (char)ASCII_character_sides); // 186 ASCII
		goTo(winW, y);
		printf("%c", (char)ASCII_character_sides);
	}

	goTo(winStartX, winH);
	printf("%c", (char)200);
	for (uint8_t x = winStartX + 1; x < winW; x++)
	{ /* Bunden */
		printf("%c", (char)205);
	}
	printf("%c", (char)188);

	// goTo(lenght,);               //MENU tekst
}

static void drawBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	// Create a simple box/square
	uint8_t x, y;
	goTo(x1, y1);			 /*The top line of the Box*/
	printf("%c", (char)218); // Top Right Corner
	for (x = x1 + 1; x < x2; x++)
	{
		printf("%c", (char)196); // Top Line
	}
	printf("%c", (char)191); // Top Left Corner

	for (y = y1 + 1; y < y2; y++)
	{							 /* The Sides  */
		goTo(x1, y);			 //   Left side
		printf("%c", (char)179); //   char is ASCII 179
		goTo(x2, y);			 //   Right side
		printf("%c", (char)179); //   char is ASCII 179
	}

	goTo(x1, y2);
	printf("%c", (char)192); // Bottom Left Corner
	for (x = x1 + 1; x < x2; x++)
	{ /* The bottom line of the Box */
		printf("%c", (char)196);
	}
	printf("%c", (char)217); // Bottom Right Corner
}

// Drawing Functions:

void DrawLineVertical(uint8_t x, uint8_t y)
{
	goTo(x, y);
	uint16_t i = 0;
	for (i = 0; i < 10; i++)
	{
		goTo(x, y + i);
		printf("%c", (unsigned char)179);
	}
}

void DrawLineHorizontal(uint8_t x, uint8_t y)
{
	goTo(x, y);
	uint16_t i = 0;
	for (i = 0; i < 10; i++)
	{
		goTo(x + i, y);
		printf("%c", (unsigned char)196);
	}
}

void DrawRightLineDiagonal(uint8_t x, uint8_t y)
{
	goTo(x, y);
	uint16_t i = 0;
	for (i = 0; i < 10; i++)
	{
		goTo(x + i, y + i);
		printf("%c", (unsigned char)92);
	}
}

void DrawLeftLineDiagonal(uint8_t x, uint8_t y)
{
	goTo(x, y);
	uint16_t i = 0;
	for (i = 0; i < 10; i++)
	{
		goTo(x - i, y + i);
		printf("%c", (unsigned char)47);
	}
}

void DrawLetterM()
{
	DrawLeftLineDiagonal(20, 10);
	DrawRightLineDiagonal(20, 10);
	DrawLeftLineDiagonal(39, 10);
	DrawRightLineDiagonal(39, 10);
}

void DrawLetterE()
{
	goTo(53, 8);
	printf("%c", (unsigned char)218);
	DrawLineVertical(53, 9);   // 53,9
	DrawLineHorizontal(54, 8); // 54,8
	DrawLineHorizontal(54, 13);
	goTo(53, 19);
	printf("%c", (unsigned char)192);
	DrawLineHorizontal(54, 19);
}

void DrawLetterN()
{
	goTo(75, 9);
	printf("%c", (unsigned char)179);
	goTo(87, 9);
	printf("%c", (unsigned char)179);

	DrawLineVertical(75, 10);
	DrawRightLineDiagonal(76, 9);
	goTo(86, 19);
	printf("%c", (unsigned char)92);

	DrawLineVertical(87, 10);
}

void DrawLetterU()
{
	DrawLineHorizontal(101, 20); // 101
	goTo(111, 20);
	printf("%c", (unsigned char)217);
	goTo(100, 19);
	printf("%c", (unsigned char)179);
	goTo(100, 20);
	printf("%c", (unsigned char)192);
	goTo(111, 19);
	printf("%c", (unsigned char)179);
	DrawLineVertical(100, 9);
	DrawLineVertical(111, 9);
}

void Draw_Text_MENU()
{
	// MENU title screen 1:
	resetBgColor();
	fgColor(5);
	DrawLetterM(); // M
	resetBgColor();
	fgColor(6);
	DrawLetterE(); // E
	resetBgColor();
	fgColor(1);
	DrawLetterN(); // N
	resetBgColor();
	fgColor(2);
	DrawLetterU(); // U
	resetBgColor();
}

void DrawPixelS(uint8_t x, uint8_t y)
{
	// Original position: x = 43, y = 42
	//  Draw pixel S:
	// First line in S
	fgColor(7);
	goTo(x, y);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	// Body of S
	goTo(x - 1, y + 1);
	printf("%c", (unsigned char)219);
	up();
	down();
	printf("%c", (unsigned char)219);

	goTo(x - 1, y + 2);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(x, y + 3);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(x + 2, y + 4);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(x - 2, y + 5);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	resetBgColor();
}

void DrawPixelT(uint8_t x, uint8_t y)
{ // x = 50, y = 42
	// Draw PIXEL T
	goTo(x, y); // 50,42
	fgColor(7);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	// T Body
	goTo(x + 2, y + 1); // 52,43
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(x + 2, y + 2); // 52,44
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(x + 2, y + 3); // 52,45
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(x + 2, y + 4); // 52,46
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(x + 2, y + 5); // 52,47
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	resetBgColor();
}

void DrawPixelA(uint8_t x, uint8_t y)
{
	// Draw A

	goTo(x, y); //(59,42)
	fgColor(7);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(x - 2, y + 1);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(64, y + 1);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(57, y + 2);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(64, y + 2);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(57, y + 3);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(57, y + 4);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(65, y + 4);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(57, y + 5);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(65, y + 5);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	resetBgColor();
}

void DrawPixelR(uint8_t x, uint8_t y)
{
	// Draw Pixel R

	goTo(x, y); // Original position: (70,42)
	fgColor(7);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(x, y + 1);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x + 5, y + 1);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(x, y + 2);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x + 5, y + 2);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(x, y + 3);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(x, y + 4);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(x, y + 5);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(x + 5, y + 5);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	resetBgColor();
}

void DrawPixelH(uint8_t x, uint8_t y)
{
	// Draw H:
	fgColor(7);
	// Left leg
	goTo(x, y); // (155,42)
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x, y + 1);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x, y + 2);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x, y + 3);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x, y + 4);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x, y + 5);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	// Middle part
	goTo(x + 1, y + 2);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	// Right Leg
	goTo(x + 6, y);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x + 6, y + 1);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x + 6, y + 2);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x + 6, y + 3);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(x + 6, y + 4);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x + 6, y + 5);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	resetBgColor();
}

void DrawPixelE(uint8_t x, uint8_t y)
{
	// Draw E:

	fgColor(7);
	goTo(x, y); //(165,42)
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	// Body
	goTo(x, y + 1);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x, y + 2);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x, y + 3);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x, y + 4);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x, y + 5);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	// Sides
	goTo(x + 2, y + 2);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(x + 2, y + 5);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	resetBgColor();
}

void DrawPixelL(uint8_t x, uint8_t y)
{
	// Draw L
	//  Body
	fgColor(7);
	goTo(x, y); //(172,42)
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x, y + 1);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x, y + 2);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x, y + 3);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x, y + 4);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x, y + 5);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	// Side
	goTo(x + 2, y + 5);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	resetBgColor();
}

void DrawPixelP(uint8_t x, uint8_t y)
{
	// Draw P
	// Body
	fgColor(7);
	goTo(x, y); //(180,42)
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(x, y + 1);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x, y + 2);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x, y + 3);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x, y + 4);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	goTo(x, y + 5);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	// Side
	goTo(x + 5, y + 1);
	printf("%c", (unsigned char)219);
	goTo(x + 5, y + 2);
	printf("%c", (unsigned char)219);
	goTo(x + 2, y + 3);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);
	printf("%c", (unsigned char)219);

	goTo(x + 6, y + 1);
	printf("%c", (unsigned char)219);
	goTo(x + 6, y + 2);
	printf("%c", (unsigned char)219);

	resetBgColor();
}

static void StartAndHelp(const gameConfig_t *config)
{
	drawBox(config->winStartX + 150, config->winStartY + 40,
			config->winStartX + 200, config->winStartY + 50); // Length of box = 55, Height of box = 10
	drawBox(config->winStartX + 33, config->winStartY + 40,
			config->winStartX + 87, config->winStartY + 50);   // Length of box = x2-x1 = 55, Height of box = y2-y1 = 10
}

void DrawStartText(uint8_t Selected)
{ // If selected == 1, blink on else off.
	blink(Selected);
	DrawPixelS(42, 50); // 43,42
	blink(Selected);
	DrawPixelT(49, 50); // 50,42
	blink(Selected);
	DrawPixelA(59, 50); // 59,42
	blink(Selected);
	DrawPixelR(70, 50); // 70,42
	blink(Selected);
	DrawPixelT(79, 50); // 80,42
	resetBgColor();
}

void DrawHelpText(uint8_t Selected)
{ // If selected == 1, blink on else off.
	blink(Selected);
	DrawPixelH(162, 50); // 155,42
	blink(Selected);
	DrawPixelE(172, 50); // 165,42
	blink(Selected);
	DrawPixelL(179, 50); // 172,42
	blink(Selected);
	DrawPixelP(187, 50); // 180,42
	resetBgColor();
}

void drawHelpScreen(const gameConfig_t *config)
{ // Draws the help screen only
	clearScreen();
	drawBordersMenu(config->winStartX, config->winStartY, config->winW, config->winH);

	DrawPixelH(config->winStartX + 95, config->winStartY + 10);	 // 60,20
	DrawPixelE(config->winStartX + 105, config->winStartY + 10); // 70,20
	DrawPixelL(config->winStartX + 112, config->winStartY + 10); // 77,20
	DrawPixelP(config->winStartX + 120, config->winStartY + 10); // 85,20

	goTo(config->winStartX + 30, config->winStartY + 30);
	fgColor(2);
		printf("How To Play");
		resetBgColor();
		goTo(30, 32);
		printf("Controls:");
		goTo(30, 34);
		printf("Joystick UP = Change shot angle");
		goTo(30, 36);
		printf("Joystick DOWN = Change shot angle");
		goTo(30, 38);
		printf("5 shot angles to choose from");
		goTo(30,40);
		printf("Joystick LEFT = Move left");
		goTo(30, 42);
		printf("Joystick RIGHT = Move right");
		goTo(30, 44);
		printf("White Button = Shoot");
		goTo(30, 46);
		printf("Red Button = Boss Key");

		goTo(100, 30);
		fgColor(4);
		printf("Objective");
		resetBgColor();
		goTo(100, 32);
		printf("Alien forces have come to take the Earth and all its minerals");
		goTo(100, 34);
		printf("You are earths last defender");
		goTo(100,36);
		printf("Destroy all the aliens and be careful of their asteroids!");
		goTo(100, 38);
		printf("Good Luck");

		goTo(170,30);
		printf("Power Ups:");
		goTo(170,32);
		printf("Lead Bullets: More damage");
		goTo(170,34);
		printf("Lightning Fuel: Faster Spaceship");
}

void Joystick_Toggle()
	{ // Uses the onboard STM_32 Joystick, can toggle left, right and click by pressing center
		joystick_inputs_init();

		while (1)
		{
			// These are for the onboard mini Joystick, not for the one we use:
			/*
			 uint8_t left = (GPIOC->IDR >> 1) & 1u;  // PC1
			 uint8_t right = (GPIOC->IDR >> 0) & 1u;  // PC0
			 uint8_t center = (GPIOB->IDR >> 5) & 1u;  // PB5
			*/
/*
			if (left)
			{ // Toggle to START
				DrawHelpText(0);
				DrawStartText(1);
				Setchoice(0);

				// simple delay to avoid flooding PuTTY
				for (volatile uint32_t i = 0; i < 9000; i++)
				{
				}
			}

			if (right)
			{ // Toggle to HELP
				DrawStartText(0);
				DrawHelpText(1);
				Setchoice(1);
				// simple delay to avoid flooding PuTTY
				for (volatile uint32_t i = 0; i < 9000; i++)
				{
				}
			}

			if (center && Getchoice())
			{ // HELP Clicked
				DrawStartText(0);
				DrawHelpText(0);
				clearScreen();
				// simple delay to avoid flooding PuTTY
				for (volatile uint32_t i = 0; i < 9000; i++)
				{
				}
				// HELP screen:
				DrawPixelH(95, 10);	 // 60,20
				DrawPixelE(105, 10); // 70,20
				DrawPixelL(112, 10); // 77,20
				DrawPixelP(120, 10); // 85,20

				goTo(30, 30);
				printf("How To Play");
				goTo(30, 32);
				printf("Controls: Joystick UP = Change shot angle");
				goTo(30, 34);
				printf("Joystick LEFT = Travel left");
				goTo(30, 36);
				printf("Joystick RIGHT = Travel right");
				goTo(30, 38);
				printf("Red Button = Shoot");
				goTo(30, 40);
				printf("? Button = Boss Key");
			}

			if (center && Getchoice() != 1)
			{ // START game Clicked
				DrawStartText(0);
				DrawHelpText(0);
				clearScreen();
				// Game Start and play here:
				//
				//
			}*/
		}
	}

// NEW

void navigator(screen_t *screen, joystick_x_t joyX, joystick_btn_t joyBtn, active_button_t *focusButton)
{
    // If nothing is focused, default to LEFT (START / MENU)
    if (*focusButton == NONE) *focusButton = LEFT;

    switch (*screen)
    {
        case MENU:
            if (joyX == JOY_X_LEFT) {
                DrawHelpText(0);
                DrawStartText(1);
                *focusButton = LEFT;
            } else if (joyX == JOY_X_RIGHT) {
                DrawStartText(0);
                DrawHelpText(1);
                *focusButton = RIGHT;
            }

            if (joyBtn == BTN_WHITE) {
                if 	(*focusButton == RIGHT) *screen = HELP;
                else if (*focusButton == LEFT) *screen = GAME; // LEFT or NONE -> GAME
            }
            break;

        case HELP:
            if (joyBtn == BTN_WHITE) *screen = MENU;
            break;

        case GAME_OVER:
            if (joyX == JOY_X_LEFT)  *focusButton = LEFT;
            if (joyX == JOY_X_RIGHT) *focusButton = RIGHT;

            if (joyBtn == BTN_WHITE) {
                if (*focusButton == LEFT)  *screen = MENU;
                else *screen = GAME;
            }
            break;

        default:
            break;
    }
}

void DrawMenuBorderAndTitle(const gameConfig_t *config)
{
	clearScreen();
	drawBordersMenu(config->winStartX, config->winStartY, config->winW, config->winH);

	DrawTitleScreen(config->winStartX + 55, config->winStartY + 10);
}

void MenuButtons(const gameConfig_t *config)
{ // Make START and HELP buttons/boxes
	StartAndHelp(config);
	DrawHelpText(0);  // Parameter is blink ON or OFF, 1 for ON and 0 for OFF
	DrawStartText(0); // Parameter is blink ON or OFF, 1 for ON and 0 for OFF
}

void ShowMenu()
{ // Starts and runs the Menu
	clearScreen();
	resetBgColor();
	goHome();
	//DrawMenuBorderAndTitle();
	//MenuButtons();
	Joystick_Toggle();
	while (1)
	{
	};
}

void drawDeathScreen(const gameConfig_t *config, const gameState_t *state)
{
    clearScreen();
    goHome();

    drawBordersMenu(config->winStartX, config->winStartY, config->winW, config->winH);

    fgColor(1);
    goTo(config->winStartX + 95, config->winStartY + 20);
    printf(" ###    ###    ##   ##  #####");
    goTo(config->winStartX + 95, config->winStartY + 21);
    printf("#      #   #   ### ###  #");
    goTo(config->winStartX + 95, config->winStartY + 22);
    printf("#  ##  #####   ## # ##  ####");
    goTo(config->winStartX + 95, config->winStartY + 23);
    printf("#   # #     #  ##   ##  #");
    goTo(config->winStartX + 95, config->winStartY + 24);
    printf(" ###  #     #  ##   ##  #####");
    resetBgColor();

    // Score
    goTo(config->winStartX + 100, config->winStartY + 35);
    printf("Final Score: %lu", state->score);
    goTo(config->winStartX + 100, config->winStartY + 37);
    printf("High Score: %lu", state->highScore);

    // Instructions
    fgColor(2);
    goTo(config->winStartX + 80, config->winStartY + 50);
    printf("Left  = Return to MENU");
    goTo(config->winStartX + 80, config->winStartY + 52);
    printf("Center = Restart Game");
    resetBgColor();

}
/*
En funktion som tegner titlen og borderen: DrawMenuBorderAndTitle();
En funktion som tegner START og HELP knapperne: MenuButtons();
En funktion som tegner HELP skærmen efter man har trykket på HELP knappen: DrawHelpScreen()
 */
