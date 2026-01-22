/*
 * math.c
 *
 *  Created on: 15 Jan 2026
 *      Author: oscar
 */

#include <stdint.h>
#include <stdio.h>
#include "math.h"

const int16_t lut[512] = {
     0,   201,   402,   603,   804,  1005,  1205,
  1406,  1606,  1806,  2005,  2205,  2404,  2603,
  2801,  2999,  3196,  3393,  3590,  3785,  3981,
  4175,  4370,  4563,  4756,  4948,  5139,  5330,
  5519,  5708,  5896,  6083,  6270,  6455,  6639,
  6822,  7005,  7186,  7366,  7545,  7723,  7900,
  8075,  8249,  8423,  8594,  8765,  8934,  9102,
  9268,  9433,  9597,  9759,  9920, 10079, 10237,
 10393, 10548, 10701, 10852, 11002, 11150, 11297,
 11441, 11585, 11726, 11865, 12003, 12139, 12273,
 12405, 12536, 12664, 12791, 12915, 13038, 13159,
 13278, 13394, 13509, 13622, 13733, 13841, 13948,
 14052, 14154, 14255, 14353, 14449, 14542, 14634,
 14723, 14810, 14895, 14977, 15058, 15136, 15212,
 15285, 15356, 15425, 15492, 15556, 15618, 15678,
 15735, 15790, 15842, 15892, 15940, 15985, 16028,
 16068, 16106, 16142, 16175, 16206, 16234, 16260,
 16283, 16304, 16323, 16339, 16352, 16363, 16372,
 16378, 16382, 16383, 16382, 16378, 16372, 16363,
 16352, 16339, 16323, 16304, 16283, 16260, 16234,
 16206, 16175, 16142, 16106, 16068, 16028, 15985,
 15940, 15892, 15842, 15790, 15735, 15678, 15618,
 15556, 15492, 15425, 15356, 15285, 15212, 15136,
 15058, 14977, 14895, 14810, 14723, 14634, 14542,
 14449, 14353, 14255, 14154, 14052, 13948, 13841,
 13733, 13622, 13509, 13394, 13278, 13159, 13038,
 12915, 12791, 12664, 12536, 12405, 12273, 12139,
 12003, 11865, 11726, 11585, 11441, 11297, 11150,
 11002, 10852, 10701, 10548, 10393, 10237, 10079,
  9920,  9759,  9597,  9433,  9268,  9102,  8934,
  8765,  8594,  8423,  8249,  8075,  7900,  7723,
  7545,  7366,  7186,  7005,  6822,  6639,  6455,
  6270,  6083,  5896,  5708,  5519,  5330,  5139,
  4948,  4756,  4563,  4370,  4175,  3981,  3785,
  3590,  3393,  3196,  2999,  2801,  2603,  2404,
  2205,  2005,  1806,  1606,  1406,  1205,  1005,
   804,   603,   402,   201,     0,  -201,  -402,
  -603,  -804, -1005, -1205, -1406, -1606, -1806,
 -2005, -2205, -2404, -2603, -2801, -2999, -3196,
 -3393, -3590, -3785, -3981, -4175, -4370, -4563,
 -4756, -4948, -5139, -5330, -5519, -5708, -5896,
 -6083, -6270, -6455, -6639, -6822, -7005, -7186,
 -7366, -7545, -7723, -7900, -8075, -8249, -8423,
 -8594, -8765, -8934, -9102, -9268, -9433, -9597,
 -9759, -9920,-10079,-10237,-10393,-10548,-10701,
-10852,-11002,-11150,-11297,-11441,-11585,-11726,
-11865,-12003,-12139,-12273,-12405,-12536,-12664,
-12791,-12915,-13038,-13159,-13278,-13394,-13509,
-13622,-13733,-13841,-13948,-14052,-14154,-14255,
-14353,-14449,-14542,-14634,-14723,-14810,-14895,
-14977,-15058,-15136,-15212,-15285,-15356,-15425,
-15492,-15556,-15618,-15678,-15735,-15790,-15842,
-15892,-15940,-15985,-16028,-16068,-16106,-16142,
-16175,-16206,-16234,-16260,-16283,-16304,-16323,
-16339,-16352,-16363,-16372,-16378,-16382,-16383,
-16382,-16378,-16372,-16363,-16352,-16339,-16323,
-16304,-16283,-16260,-16234,-16206,-16175,-16142,
-16106,-16068,-16028,-15985,-15940,-15892,-15842,
-15790,-15735,-15678,-15618,-15556,-15492,-15425,
-15356,-15285,-15212,-15136,-15058,-14977,-14895,
-14810,-14723,-14634,-14542,-14449,-14353,-14255,
-14154,-14052,-13948,-13841,-13733,-13622,-13509,
-13394,-13278,-13159,-13038,-12915,-12791,-12664,
-12536,-12405,-12273,-12139,-12003,-11865,-11726,
-11585,-11441,-11297,-11150,-11002,-10852,-10701,
-10548,-10393,-10237,-10079, -9920, -9759, -9597,
 -9433, -9268, -9102, -8934, -8765, -8594, -8423,
 -8249, -8075, -7900, -7723, -7545, -7366, -7186,
 -7005, -6822, -6639, -6455, -6270, -6083, -5896,
 -5708, -5519, -5330, -5139, -4948, -4756, -4563,
 -4370, -4175, -3981, -3785, -3590, -3393, -3196,
 -2999, -2801, -2603, -2404, -2205, -2005, -1806,
 -1606, -1406, -1205, -1005,  -804,  -603,  -402,
  -201 };


void rotateVector(vector_t *v, int32_t angleDeg) {

    //Degrees to 512
    int32_t angle512 = (angleDeg * 512) / 360;

    //Wrap
    angle512 = ((angle512 % 512) + 512) % 512;

    //sin cos (128) = (90/360) * 512
    int32_t SIN = lut[angle512];
    int32_t COS = lut[(angle512 + 128) & 511];  //& 511 bitmasking : angle512+128>512

    //x,y to 18.14
    int32_t x18 = v->x << 14;
    int32_t y18 = v->y << 14;

    //Rotation >> 14 fordi ((18.14 * 18.14) = 36.28)
    int32_t newX18 = ((x18 * COS) - (y18 * SIN)) >> 14;
    int32_t newY18 = ((x18 * SIN) + (y18 * COS)) >> 14;

    v->x = newX18 >> 14;   // back to integer
    v->y = newY18 >> 14;


    //18.14 to 16.16
    //int32_t newX16 = newX18 << 2;
    //int32_t newY16 = newY18 << 2;

}

extern shot_t shot;
void rotateShotAngle(int32_t angleDeg) {
	vector_t v;

	v.x = shot.vx >> 16; //convert to integer
	v.y = shot.vy >> 16;

	rotateVector(&v,angleDeg);

    // convert vector back to 16.16
    shot.vx = v.x << 16;
    shot.vy = v.y << 16;
}

void applyAsteroidGravity(bullet_t *b, const asteroid_t *a) {
	int16_t asteroidCenterX = a->x + (SPRITE_AST_W << 5); // We want to divide the width with 2
	int16_t asteroidCenterY = a->y + (SPRITE_AST_H << 5); // We want to divide the height with 2

	int16_t bulletDeltaX = b->x - asteroidCenterX;
	int16_t bulletDeltaY = b->y - asteroidCenterY;

	int16_t absDx = (bulletDeltaX < 0) ? -bulletDeltaX : bulletDeltaX;
	int16_t absDy = (bulletDeltaY < 0) ? -bulletDeltaY : bulletDeltaY;

	int16_t gravityRange = 7 << 6; // cells

	if (absDx <= gravityRange && absDy <= gravityRange) {

	    int16_t g = a->gravity;
	    int16_t d = (absDx > absDy) ? absDx : absDy;

	    if (d <= (int16_t)(1 << 6)) {
	        g = (int16_t)(g << 2);
	    } else if (d <= (int16_t)(2 << 6)) {
	        g = (int16_t)(g << 1);
	    } else {
	        g = (int16_t)(g >> 1);
	        if (g == 0) g = 1;
	    }

	    if (bulletDeltaX < 0)      b->vX += g;
	    else if (bulletDeltaX > 0) b->vX -= g;

	    if (bulletDeltaY < 0)      b->vY += g;
	    else if (bulletDeltaY > 0) b->vY -= g;
	}
}

void applyLorentzForce(shot_t *s, int32_t k) { //EGG
    //(x,y) -> (-y,x)
	int32_t ax = -(s->vy >> k);
    int32_t ay =  (s->vx >> k);

    s->vx += ax;
    s->vy += ay;
}


void initRandom(void)
{
    // Enable GPIOA clock
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA;

    // PA4 -> analog mode (MODER bits: 2*4 and 2*4+1)
    GPIOA->MODER &= ~(3u << (4u * 2u));
    GPIOA->MODER |=  (3u << (4u * 2u));

    // ADC1 is already enabled/calibrated in enablePots().
}

static uint16_t readNoiseADC(void)
{
    // PA4 on STM32F302 = ADC_IN5
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_1Cycles5);

    ADC_StartConversion(ADC1);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0) { }

    return ADC_GetConversionValue(ADC1);
}

uint32_t randomRange(uint32_t min, uint32_t max)
{
    if (max < min) return min;

    uint32_t span = (max - min) + 1u;

    // We build a 32-bit value from ADC noise LSBs.
    uint32_t r = 0;
    for (int i = 0; i < 32; i++)
    {
        uint16_t s = readNoiseADC();
        r = (r << 1) | (uint32_t)(s & 1u);

        // We allow for a small maount of jitter, helps to make value more random
        for (volatile int d = 0; d < 10; d++) { }
    }

    // We avoid modulo bias (random % N can favor some values slightly). Again, makes it more random.
    uint32_t limit = 0xFFFFFFFFu - (0xFFFFFFFFu % span);
    while (r >= limit)
    {
        // Generate 32 bits
        r = 0;
        for (int i = 0; i < 32; i++)
        {
            uint16_t s = readNoiseADC();
            r = (r << 1) | (uint32_t)(s & 1u);
            for (volatile int d = 0; d < 10; d++) { }
        }
    }

    return min + (r % span);
}

