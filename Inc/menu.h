
#ifndef _MENU_H_
#define _MENU_H_

	/* ----- Dependencies ----- */
	#include <stdint.h>
	#include <stdio.h>
	#include "game_master.h"

	/* ----- Functions ----- */
	void DrawBordersMenu(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, const char *title);
	void DrawBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

	void DrawLineVertical(uint8_t x,uint8_t y);
	void DrawLineHorizontal(uint8_t x, uint8_t y);
	void DrawRightLineDiagonal (uint8_t x, uint8_t y);
	void DrawLeftLineDiagonal(uint8_t x, uint8_t y);

	void DrawLetterM();
	void DrawLetterE();
	void DrawLetterN();
	void DrawLetterU();

	void DrawPixelS(uint8_t x, uint8_t y);
	void DrawPixelT(uint8_t x, uint8_t y);
	void DrawPixelA();
	void DrawPixelR();
	void DrawPixelH(uint8_t x, uint8_t y);
	void DrawPixelE(uint8_t x, uint8_t y);
	void DrawPixelL(uint8_t x, uint8_t y);
	void DrawPixelP(uint8_t x, uint8_t y);

	void DrawPixelM(uint8_t x, uint8_t y);

	void StartAndHelp();
	void DrawStartText(uint8_t Selected);
	void DrawHelpText(uint8_t Selected);

	void joystick_inputs_init();
	void Joystick_Toggle();
	void Setchoice (int value);
	int Getchoice(void);

	void Draw_Text_MENU();

	void ShowMenu(const gameConfig_t *config, const joystick_input_t *joyInput);
	void ShowDeathScreen(const gameConfig_t *config, gameState_t *state, const joystick_input_t *joyInput);


#endif
