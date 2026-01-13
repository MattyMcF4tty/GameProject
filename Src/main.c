#include "main.h"

static void initBoard() {
	uart_init(9600); // Set UART

	/* ---- Enable necessary GPIO's ----- */
	gpioEnable(GPIOA);
	gpioEnable(GPIOB);
	gpioEnable(GPIOC);

	return;
}

int main() {
	initBoard();

	while(1){}
}
