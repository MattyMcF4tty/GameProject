
/*
X-axis potentiometer is connected to PC2
Y-axis potentiometer is connected to PC3
Red button is connected to PC0
White button is connected to PC1
 */


#include "joystick30010.h"

/* ---------- Local Joystick function ---------- */
static joystick_y_t readPotYaxis();
static joystick_x_t readPotXaxis();
static joystick_btn_t readButton();

/* ---------- Definitions ---------- */
#define ADC_MID     2048
#define DEADZONE    200				// tune able

/* ---------- Public joystick functions ---------- */
void readJoystick(joystick_input_t *joyInput)
{


    // 1) Read raw hardware state
    joystick_x_t   newX   = readPotXaxis();
    joystick_y_t   newY   = readPotYaxis();
    joystick_btn_t newBtn = readButton();

    if (newX != joyInput->xAxis) 	joyInput->xAxis = newX;
    if (newY != joyInput->yAxis) 	joyInput->yAxis = newY;
    if (newBtn != joyInput->button)	joyInput->button = newBtn;
}

// Enable clock for GPIO ports
void enableGpioClock(void) {
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA;
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC;
}

void enablePots(void) {
	// PC2 analog
	GPIOC->MODER &= ~(3 << (2 * 2));
	GPIOC->MODER |=  (3 << (2 * 2));

	// PC3 analog
	GPIOC->MODER &= ~(3 << (3 * 2));
	GPIOC->MODER |=  (3 << (3 * 2));

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

static joystick_x_t readPotXaxis() {

	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_1Cycles5);

	ADC_StartConversion(ADC1); // Start ADC read
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read
	uint16_t x = ADC_GetConversionValue(ADC1); // Read the ADC value


	if (x > 3900)
		return JOY_X_RIGHT; 			// Joystick moved to the right
	else if (x < 1500)
		return JOY_X_LEFT; 				// Joystick moved to the left
	else
		return JOY_X_NONE; 				// Fallback
}

static joystick_y_t readPotYaxis() {
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_1Cycles5);

	ADC_StartConversion(ADC1); // Start ADC read
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0); // Wait for ADC read
	uint16_t x = ADC_GetConversionValue(ADC1); // Read the ADC value

	if (x > 3900)
		return JOY_Y_UP; 				//Joystick moved up
	else if (x < 1500)
		return JOY_Y_DOWN; 				//Joystick moved down
	else
		return JOY_Y_NONE;				// Fallback
}


static joystick_btn_t readButton() {

	// red button (Boss key), takes precedence over white button
	if (GPIOC->IDR & (0x0001 << 0)) { // Read red button
		return BTN_RED;
	} else if ((GPIOC->IDR & (0x0001 << 1)) >> 1) { // Read white button
		return BTN_WHITE;
	} else {
		return BTN_NONE;
	}
}








