#include "ansi.h"


#define ESC 0x1B

void goHome() {
	// Fetches the cursor position
	printf("%c[H", ESC);
}

void clearScreen() {
	// Clears screen
	printf("%c[2J", ESC);
}

void clearLine(uint8_t y) {
	// Clears line
	goTo(0, y);
	printf("%c[2K", ESC);
}

void goTo(uint8_t x, uint8_t y) {
	// Moves cursor to x and y
	printf("%c[%d;%dH", ESC, y, x);
}

void goToCoords(int16_t x, int16_t y) {

    x >>= 6; // Convert x to integer
    y >>= 6; // Convert y to integer

	printf("%c[%d;%dH", ESC, y, x);
}

void fgColor(uint8_t foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/

  printf("%c[%dm", ESC, foreground+30);
}

void bgColor(uint8_t background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void resetBgColor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}
