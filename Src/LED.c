#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "game_master.h"



void LEDinitializer() {
	//Configure the LED pins as outputs

	// Enable clock til A, B, C
	    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN;

	    // MODER = 00 -> input
	    GPIOA->MODER &= ~(3u << (4u * 2u));   // PA4
	    GPIOB->MODER &= ~(3u << (0u * 2u));   // PB0
	    GPIOB->MODER &= ~(3u << (5u * 2u));   // PB5
	    GPIOC->MODER &= ~(3u << (0u * 2u));   // PC0
	    GPIOC->MODER &= ~(3u << (1u * 2u));   // PC1

	    // PUPDR: typisk eksterne pulldowns på boardet -> "no pull" (00) er fint
	    GPIOA->PUPDR &= ~(3u << (4u * 2u));
	    GPIOB->PUPDR &= ~(3u << (0u * 2u));
	    GPIOB->PUPDR &= ~(3u << (5u * 2u));
	    GPIOC->PUPDR &= ~(3u << (0u * 2u));
	    GPIOC->PUPDR &= ~(3u << (1u * 2u));


		//Red PB4
		GPIOB->MODER &= ~(3 << (4 * 2));
		GPIOB->MODER |=  (1 << (4 * 2));

		GPIOB->OTYPER &= ~(1 << 4);
		GPIOB->OSPEEDR |= (2 << (4 * 2));

		// Green PC7
		GPIOC->MODER &= ~(3 << (7 * 2));
		GPIOC->MODER |=  (1 << (7 * 2));

		GPIOC->OTYPER &= ~(1 << 7);
		GPIOC->OSPEEDR &= ~(3 << (7 * 2));
		GPIOC->OSPEEDR |= (2 << (7 * 2));

		// Blue PA9
		GPIOA->MODER &= ~(3 << (9 * 2));
		GPIOA->MODER |=  (1 << (9 * 2));

		GPIOA->OTYPER &= ~(1 << 9);
		GPIOA->OSPEEDR &= ~(3 << (9 * 2));
	    GPIOA->OSPEEDR |= (2 << (9 * 2));

	    // Turn all LEDs off
	          GPIOB->ODR |= (1 << 4); // Red off
	          GPIOC->ODR |= (1 << 7); // Green off
	          GPIOA->ODR |= (1 << 9); // Blue off


	   //Turn Blue ON:
	   // GPIOA->ODR &= ~(1 << 9);
	   //Turn Red ON:
	   // GPIOB->ODR &= ~(1 << 4);
	   //Turn Green ON:
	   // GPIOC->ODR &= ~(1 << 7);


	// simple delay to avoid flooding PuTTY
	     for (volatile uint32_t i = 0; i < 90000; i++) { }

}


void ThreeLives() {
    GPIOB->ODR |= (1 << 4); // Red off
    GPIOC->ODR |= (1 << 7); // Green off
    GPIOA->ODR |= (1 << 9); // Blue off
	 //Turn Green ON:
	  GPIOC->ODR &= ~(1 << 7);

}

void TwoLives() {
    GPIOA->ODR |= (1 << 9); // Blue off
	 //Yellow
	//Turn Red ON:
	GPIOB->ODR &= ~(1 << 4);
    //Turn Green ON:
    GPIOC->ODR &= ~(1 << 7);

}

void OneLife() {
    GPIOC->ODR |= (1 << 7); // Green off
    GPIOA->ODR |= (1 << 9); // Blue off
    //Turn Red ON:
    GPIOB->ODR &= ~(1 << 4);

}

void NoLife() {
	 GPIOB->ODR |= (1 << 4); // Red off
	 GPIOC->ODR |= (1 << 7); // Green off
	 GPIOA->ODR |= (1 << 9); // Blue off

}




void LEDLives(uint8_t lives) {   //LEDinitializer() + LEDLives to work

	if (lives >= 3) {
		ThreeLives();
	}

	else if (lives == 2) {
		TwoLives();
	}

	else if (lives == 1) {
		OneLife();
	}

	else {
		NoLife();
	}
}

