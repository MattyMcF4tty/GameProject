/*
 * timer.c
 *
 *  Created on: 15 Jan 2026
 *      Author: oscar
 */

#include "timer.h"

static volatile uint8_t tick = 0;
static volatile stopwatch_time_t sw = {0,0,0,0};


uint8_t timerTickOccurred(void) {
	if (tick) {
		tick = 0;
		return 1;
	}
	return 0;
}

void timerGetTimer(stopwatch_time_t *t) {
	t -> hs = sw.hs;
	t -> s = sw.s;
	t -> m = sw.m;
	t -> h = sw.h;
}

void timerInit(void) {
	RCC->APB2ENR |= RCC_APB2Periph_TIM15;

    TIM15->CR1 = 0;
    TIM15->PSC = 6399;	// 10 kHz counter clock (64 MHz timer clock)
    // TIM15->ARR = 332;	// ~30 FPS (tick ≈ 33.3 ms)
    TIM15->ARR = 416;	// ~24 FPS (tick ≈ 41.7 ms)

    TIM15->EGR = TIM_EGR_UG; // load PSC/ARR immediately
    TIM15->SR  = 0;          // clear pending flags

    TIM15->DIER |= TIM_DIER_UIE;     // update interrupt enable

    NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 1);
    NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);

}

void TIM1_BRK_TIM15_IRQHandler(void) {
	if (TIM15->SR & TIM_SR_UIF) {
		TIM15->SR &= ~TIM_SR_UIF; //Clear Update

		tick = 1;
		sw.hs++;

		if (sw.hs >= 100) {
			sw.hs = 0;
			sw.s++;
		}
		if (sw.s >= 60) {
			sw.s = 0;
			sw.m++;
		}
		if (sw.m >= 60) {
			sw.m = 0;
			sw.h++;
		}
	}
}


void timerStart(void) {
	timerInit();
	TIM15->CR1 |= TIM_CR1_CEN;
}

void timerStop(void) {
	TIM15->CR1 &= ~(TIM_CR1_CEN);
}

void timerReset(void) {
	TIM15->CR1 &= ~(TIM_CR1_CEN);

	sw.hs = 0;
	sw.s = 0;
	sw.m = 0;
	sw.h = 0;

	tick = 0;
}
