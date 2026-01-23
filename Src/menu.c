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

static void DrawPixelS(uint8_t x, uint8_t y)
{
	// Original position: x = 43, y = 42
	//  Draw pixel S:
	// First line in S
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


}

static void DrawPixelT(uint8_t x, uint8_t y)
{ // x = 50, y = 42
	// Draw PIXEL T
	goTo(x, y); // 50,42

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

}

static void DrawPixelA(uint8_t x, uint8_t y)
{
	// Draw A

	goTo(x, y); //(59,42)

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

}

static void DrawPixelR(uint8_t x, uint8_t y)
{
	// Draw Pixel R

	goTo(x, y); // Original position: (70,42)

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

}

static void DrawPixelH(uint8_t x, uint8_t y)
{
	// Draw H:

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


}

static void DrawPixelE(uint8_t x, uint8_t y)
{
	// Draw E:

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


}

static void DrawPixelL(uint8_t x, uint8_t y)
{
	// Draw L
	//  Body

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


}

static void DrawPixelP(uint8_t x, uint8_t y)
{
	// Draw P
	// Body

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


}

static void StartAndHelp(const gameConfig_t *config)
{
	drawBox(config->winStartX + 130, config->winStartY + 40,   // 150,40 HELP box
			config->winStartX + 180, config->winStartY + 50);  // 200,50 HELP box
	drawBox(config->winStartX + 33, config->winStartY + 40,    // START box
			config->winStartX + 87, config->winStartY + 50);   // START box
}

void DrawStartText(uint8_t Selected)
{ // If selected == 1, blink on else off.
	if (Selected == 1) {
		fgColor(2);
		DrawPixelS(42, 50); // 43,42
		DrawPixelT(49, 50); // 50,42
		DrawPixelA(59, 50); // 59,42
		DrawPixelR(70, 50); // 70,42
		DrawPixelT(79, 50); // 80,42
		resetBgColor();
	}
	else if (Selected == 0) {
		fgColor(7);
		DrawPixelS(42, 50); // 42
		DrawPixelT(49, 50); // 49
		DrawPixelA(59, 50); // 59
		DrawPixelR(70, 50); // 70
		DrawPixelT(79, 50); // 79
		resetBgColor();

	}

}

void DrawHelpText(uint8_t Selected)
{ // If selected == 1, blink on else off.
	if (Selected == 1) {
			fgColor(2);
			DrawPixelH(142, 50); // 162
			DrawPixelE(152, 50); // 172
			DrawPixelL(159, 50); // 179
			DrawPixelP(168, 50); // 187
			resetBgColor();
		}
		else if (Selected == 0) {
			fgColor(7);
			DrawPixelH(142, 50); // 155,42
			DrawPixelE(152, 50); // 165,42
			DrawPixelL(159, 50); // 172,42
			DrawPixelP(168, 50); // 180,42
			resetBgColor();

		}

}

void drawHelpScreen(const gameConfig_t *config)
{ // Draws the help screen only
	clearScreen();
	drawBordersMenu(config->winStartX, config->winStartY, config->winW, config->winH);

	DrawPixelH(config->winStartX + 85, config->winStartY + 10);	 // 60,20
	DrawPixelE(config->winStartX + 95, config->winStartY + 10); // 70,20
	DrawPixelL(config->winStartX + 102, config->winStartY + 10); // 77,20
	DrawPixelP(config->winStartX + 110, config->winStartY + 10); // 85,20

	goTo(config->winStartX + 30, config->winStartY + 30);
	fgColor(2);

		resetBgColor();
		goTo(20, 30);
		fgColor(6);
		printf("Controls:");
		resetBgColor();
		goTo(20, 32);
		printf("Joystick UP = Change shot angle");
		goTo(20, 34);
		printf("Joystick DOWN = Change shot angle");
		goTo(20, 36);
		printf("5 shot angles to choose from");
		goTo(20,38);
		printf("Joystick LEFT = Move left");
		goTo(20, 40);
		printf("Joystick RIGHT = Move right");
		goTo(20, 42);
		printf("White Button = Shoot");
		goTo(20, 44);
		printf("Red Button = Boss Key");

		goTo(75, 30);
		fgColor(2);
		printf("Objective");
		resetBgColor();
		goTo(75, 32);
		printf("Alien forces have come to take the Earth and all its minerals");
		goTo(75, 34);
		printf("You are earths last defender");
		goTo(75,36);
		printf("Destroy all the aliens and be careful of their asteroids!");
		goTo(75, 38);
		printf("Good Luck");

		goTo(160,30);
		fgColor(1);
		printf("Power Ups:");
		resetBgColor();
		goTo(160,32);
		printf("Lead Bullets: More damage");
		goTo(160,34);
		printf("Lightning Fuel: Faster Spaceship");
}


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
    printf("Hold Left and click white button  = Return to MENU");
    goTo(config->winStartX + 80, config->winStartY + 52);
    printf("Hold right and click white button = Restart Game");
    resetBgColor();

}
