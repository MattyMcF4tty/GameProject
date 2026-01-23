
#ifndef _MENU_H_
#define _MENU_H_

	/* ----- Dependencies ----- */
	#include <stdint.h>
	#include <stdio.h>
	#include "game_master.h"

	/* ----- Type definitions ----- */
	typedef enum {
		LEFT,
		RIGHT,
		NONE,
	} active_button_t;

	/* ----- Functions ----- */

	void DrawPixelS(uint8_t x, uint8_t y);
	void DrawPixelT(uint8_t x, uint8_t y);
	void DrawPixelA(uint8_t x, uint8_t y);
	void DrawPixelR(uint8_t x, uint8_t y);
	void DrawPixelH(uint8_t x, uint8_t y);
	void DrawPixelE(uint8_t x, uint8_t y);
	void DrawPixelL(uint8_t x, uint8_t y);
	void DrawPixelP(uint8_t x, uint8_t y);

	void DrawStartText(uint8_t Selected);
	void DrawHelpText(uint8_t Selected);

	void joystick_inputs_init();
	void Joystick_Toggle();
	void Setchoice (int value);
	int Getchoice();

	void ShowMenu();
	void ShowDeathScreen(const gameConfig_t *config, gameState_t *state, const joystick_input_t *joyInput);

	void DrawTitleScreen(uint8_t startX, uint8_t startY);

	void DrawMenuBorderAndTitle(const gameConfig_t *config);
	void navigator(screen_t *screen, joystick_x_t joyX, joystick_btn_t joyBtn, active_button_t *focusButton);
	void MenuButtons(const gameConfig_t *config);

	void drawBordersMenu(uint8_t winStartX, uint8_t winStartY, uint8_t winW, uint8_t winH);
	void drawHelpScreen(const gameConfig_t *config);
	void drawDeathScreen(const gameConfig_t *config, const gameState_t *state);

#endif
