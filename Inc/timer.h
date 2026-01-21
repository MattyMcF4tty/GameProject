/*
 * timer.h
 *
 *  Created on: 15 Jan 2026
 *      Author: oscar
 */



#ifndef _TIMER_H_
#define _TIMER_H_


	/* ----- Dependencies ----- */
	#include <stdint.h>
	#include <stdio.h>
	#include "stm32f30x_conf.h"

	/* ----- Type definitions ----- */
	typedef struct {
		volatile uint8_t hs;   // hundredths
		volatile uint8_t s;    // seconds
		volatile uint8_t m;    // minutes
		volatile uint8_t h;    // hours
	} stopwatch_time_t;

	/* ----- Functions ----- */
	uint8_t timerTickOccurred(void);
	void timerGetTimer(stopwatch_time_t *t);
	void timerInit(void);
	void TIM1_BRK_TIM15_IRQHandler(void);
	void timerStart(void);
	void timerStop(void);
	void timerReset(void);



#endif
