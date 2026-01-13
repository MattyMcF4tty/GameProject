#include "stm32_helpers.h"

void gpioEnable(GPIO_TypeDef *GPIO) {
	if 		(GPIO == GPIOA)	RCC->AHBENR |= RCC_AHBPeriph_GPIOA;
	else if (GPIO == GPIOB) RCC->AHBENR |= RCC_AHBPeriph_GPIOB;
	else if (GPIO == GPIOC) RCC->AHBENR |= RCC_AHBPeriph_GPIOC;
	else if (GPIO == GPIOD) RCC->AHBENR |= RCC_AHBPeriph_GPIOD;
	else if (GPIO == GPIOE) RCC->AHBENR |= RCC_AHBPeriph_GPIOE;
	else if (GPIO == GPIOF) RCC->AHBENR |= RCC_AHBPeriph_GPIOF;
}

uint8_t gpioReadPin(GPIO_TypeDef *GPIO, uint8_t pin) {

		pin = pin > 15 ? 15 : pin; // cap pin at 15

		return (GPIO->IDR >> pin) & 1u;
}

void gpioSetModer(GPIO_TypeDef *GPIO, uint8_t pin, uint8_t moderState) {
	// moderState:
	// 0 = Input
	// 1 = Output
	// 2 = Alternate Function
	// 3 = Analog in/out

	if (pin > 15) {
		printf("WARNING: There is no moder pin %d, max is 15!", pin);
		return;
	}

	moderState = moderState > 3 ? 3 : moderState; // Cap moderState at 3
	// Clear mode
	GPIO->MODER &= ~(0x03 << (pin * 2));

	GPIO->MODER |= (moderState << (pin * 2));
}

void gpioSetPin(GPIO_TypeDef *GPIO, uint8_t pin, uint8_t value) {

	if (pin > 15) {
		printf("WARNING: There is no pin %d, max is 15!", pin);
		return;
	}


	value = value >= 1; // Cap value at 1

	// Clear pin
	GPIO->ODR &= ~(1u << pin);

	// Set pin
	GPIO->ODR |= (value << pin);
}

void gpioSetPull(GPIO_TypeDef *GPIO, uint8_t pin, uint8_t pullState) {
	// 0 = No pull
	// 1 = Pull up
	// 2 = Pull down

	if (pin > 15) {
		printf("WARNING: There is no moder pin %d, max is 15!", pin);
		return;
	}

	pullState = pullState > 2 ? 2 : pullState; // Cap pullState at 2

	// Clear previous value
	GPIO->PUPDR &= ~(0x3 << (pin * 2));

	GPIO->PUPDR |= (pullState << (pin * 2));
}
