#include "main.h"

volatile int frame = 0;

void vblank() {
    frame++;
}

int main() {
    touchPosition touchXY;

    irqSet(IRQ_VBLANK, vblank);

    consoleDemoInit();

    printf("      Hello DS dev'rs\n");
    printf("     \x1b[32mwww.devkitpro.org\n");
    printf("   \x1b[32;1mwww.drunkencoders.com\x1b[39m");

    while (true) {
        swiWaitForVBlank();
        scanKeys();
        int keys = keysDown();
        if (keys & KEY_START) {
            break;
        }

        touchRead(&touchXY);

        // print at using ansi escape sequence \x1b[line;columnH
        printf("\x1b[10;0HFrame = %d", frame);
        printf("\x1b[16;0HTouch x = %04X, %04X\n", touchXY.rawx, touchXY.px);
        printf("Touch y = %04X, %04X\n", touchXY.rawy, touchXY.py);
    }

    return 0;
}
