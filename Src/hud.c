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
void drawHud(void)
{
    // --- Draw score ---
    clearLine(HUD_SCORE_Y);
    goTo(1, HUD_SCORE_Y);

    printf("Score: %u", currentScore);

    // --- Draw lives ---
    clearLine(HUD_LIVES_Y);
    goTo(1, HUD_LIVES_Y);

    printf("Lives: ");

    for (uint8_t i = 0; i < currentLives; i++) {
        printf("♥ ");   //sprite heart here not added yet
    }
}

void hudLoseLife(void)
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
void updateScore(void)
{
    stopwatch_time_t t;
    timerGetTimer(&t);

    // Total seconds elapsed
    uint32_t totalSeconds = t.h * 3600 + t.m * 60 + t.s;

    if (totalSeconds > lastTotalSeconds) {
        // Quadratic growth: score increases faster as time passes
        currentScore += (totalSeconds * totalSeconds - lastTotalSeconds * lastTotalSeconds) / 10;

        lastTotalSeconds = totalSeconds; // update for next second
    }
}

uint16_t hudGetScore(void) {
    return currentScore;
}



