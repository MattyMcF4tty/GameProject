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

static uint8_t currentLives = 3;
static uint16_t currentScore = 0;


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
        //printf("♥ ");   sprite heart here not added yet
    }
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
void updateScore(void)
{
    stopwatch_time_t t;
    timerGetTimer(&t);

    // score increases each second score = seconds + (minutes*60)
    currentScore = t.s + (t.m * 60);
}
