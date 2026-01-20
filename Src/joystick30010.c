/*
X-axis potentiometer is connected to PA0
Y-axis potentiometer is connected to PA1
Red button is connected to PC0
White button is connected to PC1
 */

#include "joystick30010.h"


// Enable clock for GPIO ports
void enableGpioClock(void) {
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA;
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC;
}

void enablePots(void) {
	GPIOA->MODER &= ~(3 << (0 * 2));// Clear mode btis for PA0
	GPIOA->MODER |= (3 << (0 * 2)); // PA0 Analog mode
	GPIOA->MODER &= ~(3 << (0 * 2));// Clear mode btis for PA1
	GPIOA->MODER |= (3 << (1 * 2)); // PA1 Analog mode

	RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12; // Clear ADC12 prescaler bits
	RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV6; // Set ADC12 prescaler to 6
	RCC->AHBENR |= RCC_AHBPeriph_ADC12; // Enable clock for ADC12

	ADC1->CR = 0x00000000; // Clear CR register
	ADC1->CFGR &= 0xFDFFC007; // Clear ADC1 config register
	ADC1->SQR1 &= ~ADC_SQR1_L; // Clear regular sequence register 1

	ADC1->CR |= 0x10000000; // Enable internal ADC voltage regulator
	for (int i = 0 ; i < 1000 ; i++) {} // Wait for about 16 microseconds

	ADC1->CR |= 0x80000000; // Start ADC1 calibration
	while (!(ADC1->CR & 0x80000000)); // Wait for calibration to finish
	for (int i = 0 ; i < 100 ; i++) {} // Wait for a little while

	ADC1->CR |= 0x00000001; // Enable ADC1 (0x01 - Enable, 0x02 - Disable)
	while (!(ADC1->ISR & 0x00000001)); // Wait until ready
}

void enableButtons(void) {

	GPIOC->MODER &= ~(0x00000003 << (0 * 2)); //Set PC0 to input mode
	GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Set PC1 to inpu mode

	GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear PUPDR for PC0
	GPIOC->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear PUPDR for PC1

	GPIOC->PUPDR |= (0x00000002 << (0 * 2)); // Set PC0 to pull-down mode
	GPIOC->PUPDR |= (0x00000002 << (1 * 2)); //Set PC1 to pull-down mode


}

void enableJoystick(){
	enableGpioClock(); // Enable the clock function of the ports
	enableButtons(); // Enable buttons
	enablePots(); //  Enable the two potentiometers
}

int8_t readPotXaxis(void) {

	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_1Cycles5);

	ADC_StartConversion(ADC1); // Start ADC read
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read
	uint16_t x = ADC_GetConversionValue(ADC1); // Read the ADC value


	if (x > 100)
		return 0; // Joystick moved to the right

	else if (x < 8)
		return 1; // Joystick moved to the left

	else if (x > 8 && x < 100)
		return 2; // Joystick in deadzone

	return 5; // Backup returnvalue to prevent undefined behaviour

}

int8_t readPotYaxis(void){
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_1Cycles5);

	ADC_StartConversion(ADC1); // Start ADC read
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read
	uint16_t x = ADC_GetConversionValue(ADC1); // Read the ADC value

	if (x > 4040)
		return 0; //Joystick moved up

	else if (x < 3500)
		return 1; //Joystick moved down

	else if (x > 3500 && x < 4040)
		return 2; //Joystick in deadzone

	return 5;// Backup returnvalue to prevent undefined behaviour

}


int16_t readButton(int8_t pin) {
	// when pin=0 then the red button is read
	// when pin=1 then the white button is read

	int8_t button_value = 0;
	if (pin == 0) {
		button_value = (GPIOC->IDR & (0x0001 << 0));
	}

	else if (pin == 1) {
	button_value = ((GPIOC->IDR & (0x0001 << 1)) >> 1); // Read PC1 and shift the result to be either 1 or 0
	}

	return button_value;
}








