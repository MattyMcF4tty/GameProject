/*
 * math.h
 *
 *  Created on: 15 Jan 2026
 *      Author: oscar
 */



#ifndef _MATH_H_
#define _MATH_H_

	/* ----- Dependencies ----- */
	#include <stdint.h>
	#include "game_master.h"
	#include "sprites.h"

	/* ----- Type definitions ----- */
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

	/* ----- Functions ----- */
	void rotateVector(vector_t *v, int32_t angleDeg);
	void printFix(int32_t i);
	void rotateShotAngle(int32_t angleDeg);
	void applyAsteroidGravity(bullet_t *b, const asteroid_t *a);
	void applyLorentzForce(shot_t *s, int32_t k);

#endif
