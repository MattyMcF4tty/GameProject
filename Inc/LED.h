
#ifndef LED_H_
#define LED_H_

/* ----- Dependencies ----- */
#include <stdint.h>
#include <stdio.h>

/* Functions */
void LEDinitializer();
void ThreeLives();
void TwoLives();
void OneLife();
void NoLife();
void LEDLives(uint8_t lives);

#endif /* LED_H_ */
