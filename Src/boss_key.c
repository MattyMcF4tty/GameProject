#include "boss_key.h"

void bossKey(void)
{
    int row, col;
    int value = 1000;

    clearScreen();
    goTo(1,1);

    // Title
    printf("                Q3 FINANCIAL SUMMARY\n");
    printf("                --------------------\n\n");

    // Column headers
    printf("     ");
    for (col = 1; col <= 10; col++) {
        printf("  C%-3d", col);
    }
    printf("\n");

    // Data rows
    for (row = 1; row <= 15; row++){
        printf("R%-3d ", row);

        for (col = 1; col <= 10; col++){
            printf("%6d", value);
            value += (row + col);
        }
        printf("\n");
    }
}
