#ifndef _JOYSTICK30010_H_
#define _JOYSTICK30010_H_

	/* ----- Dependencies ----- */
	#include "30010_io.h" // Input/output library for this course
	#include "stm32f30x_conf.h" // STM32 config
	#include "stdint.h"
	#include "stdio.h"

	/* ----- Type definitions ----- */
	typedef enum {
		JOY_Y_UP,
		JOY_Y_DOWN,
		JOY_Y_NONE
	} joystick_y_t;

	typedef enum {
		JOY_X_LEFT,
		JOY_X_RIGHT,
		JOY_X_NONE
	} joystick_x_t;

	typedef enum {
		BTN_RED,
		BTN_WHITE,
		BTN_NONE
	} joystick_btn_t;

	typedef struct {
		joystick_x_t xAxis;
		joystick_y_t yAxis;
		joystick_btn_t button;
	} joystick_input_t;

	/* ----- Functions ----- */
	void readJoystick(joystick_input_t *joyInput, joystick_input_t *prevJoyInput);

	void enableJoystick();
	void enableGpioClock();
	void enablePots();
	void enableButtons();


#endif
