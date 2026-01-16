/*
 * hud.h
 *
 *  Created on: 16 Jan 2026
 *      Author: oscar
 */

#include <stdint.h>
#include <stdio.h>
#include "stm32f30x_conf.h"

#ifndef HUD_H_
#define HUD_H_

drawHud(void);
updateLives(uint8_t *lives);
updateScores(uint8_t *score);

#endif /* HUD_H_ */
