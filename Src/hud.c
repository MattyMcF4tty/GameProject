/*
 * hud.c
 *
 *  Created on: 16 Jan 2026
 *      Author: oscar
 */


#include <stdint.h>
#include <stdio.h>

#include "ansi.h"
#include "hud.h"
#include "timer.h"

#define HUD_SCORE_Y   1     // top line
#define HUD_LIVES_Y   2     // second line

uint8_t currentLives = 3;
uint16_t currentScore = 0;
static uint32_t lastTotalSeconds = 0;


//------------------------------------------------------
// Draw the entire HUD (score + lives)
//------------------------------------------------------
void drawHud(const gameConfig_t *config, const gameState_t *state)
{
	fgColor(7);
	resetBgColor();
	uint8_t scoreY = config->winStartY - 1;
	uint8_t livesY = config->winStartY - 2;
	uint8_t levelY = config->winStartY - 3;

    // --- Draw score ---
    clearLine(scoreY);
    goTo(config->winStartX, scoreY);

    printf("Score: %lu", (unsigned long)state->score);

    // --- Draw lives ---
    clearLine(livesY);
    goTo(config->winStartX, livesY);

    printf("Lives: ");

    for (uint8_t i = 0; i < state->lives; i++) {
        printf("♥ ");   //sprite heart here not added yet
    }

    clearLine(levelY);
    goTo(config->winStartX, levelY);
    printf("Level: %u ", state->level);

}

void hudLoseLife()
{
    if (currentLives > 0)
        currentLives--;
}

uint8_t hudGetLives(void)
{
    return currentLives;
}


//------------------------------------------------------
// Update score using the timer
//------------------------------------------------------
void updateScore(uint32_t *score)
{
    stopwatch_time_t t;
    timerGetTimer(&t);

    // Total seconds elapsed
    uint32_t totalSeconds = t.h * 3600 + t.m * 60 + t.s;

    if (totalSeconds > lastTotalSeconds) {
        // Quadratic growth: score increases faster as time passes
        *score += (totalSeconds * totalSeconds - lastTotalSeconds * lastTotalSeconds) / 10;

        lastTotalSeconds = totalSeconds; // update for next second
    }
}

uint16_t hudGetScore(void) {
    return currentScore;
}



