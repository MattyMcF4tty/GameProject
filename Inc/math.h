/*
 * math.h
 *
 *  Created on: 15 Jan 2026
 *      Author: oscar
 */

#include <stdint.h>

#ifndef MATH_H_
#define MATH_H_

typedef struct {
    int32_t x, y;
} vector_t;
typedef struct {
    int32_t x;      // 16.16 position
    int32_t y;      // 16.16 position
    int32_t vx;     // 16.16 vector
    int32_t vy;
    uint8_t active;
} shot_t;

typedef struct {
    int32_t x;
    int32_t y;
    int32_t vx;
    int32_t vy;
    uint8_t active;
} asteroid_t;


void rotateVector(vector_t *v, int32_t angleDeg);
void printFix(int32_t i);
void rotateShotAngle(int32_t angleDeg);
void applyAsteroidGravity(shot_t *s, asteroid_t *a);
void applyLorentzForce(shot_t *s, int32_t k);

#endif /* MATH_H_ */
