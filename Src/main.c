#include "main.h"

static void initBoard() {
	uart_init(115200); // Set UART

	/* ---- Enable necessary GPIO's ----- */
	gpioEnable(GPIOA);	// Joystick,
	gpioEnable(GPIOB);	// Joystick,
	gpioEnable(GPIOC);	// Joystick,

	return;
}

int main() {
    initBoard(); // Should always be first



    while (1) {
        if (gameMode == STATE_MENU) {
            ShowMenu();
        }
        else if (gameMode == STATE_GAME) {
            updateGame();
        }
        else if (gameMode == STATE_GAME_OVER) {
            ShowDeathScreen();
        }
    }


}
