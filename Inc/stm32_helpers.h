#ifndef _STM32_HELPERS_H_
#define _STM32_HELPERS_H_

	/* ----- Dependencies ----- */
	#include <stdint.h>
	#include "stm32f30x_conf.h" // STM32 config
	#include "30010_io.h" // Input/output library for this course

	/* ----- Functions ----- */
	void gpioEnable(GPIO_TypeDef *GPIO); 									// Enables GPIO, A -> F
	uint8_t gpioReadPin(GPIO_TypeDef *GPIO, uint8_t pin); 					// Reads and returns a specified pin from a GPIO
	void gpioSetModer(GPIO_TypeDef *GPIO, uint8_t pin, uint8_t moderState);	// Sets GPIO mode
	void gpioSetPin(GPIO_TypeDef *GPIO, uint8_t pin, uint8_t value);		// Sets GPIO pin to a specified value
	void gpioSetPull(GPIO_TypeDef *GPIO, uint8_t pin, uint8_t pullState);	// Sets a GPIO pin's pull state

#endif
