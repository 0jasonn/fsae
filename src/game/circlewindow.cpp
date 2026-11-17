#include "engine/functions.h"
#include "game/triangle.h"

extern u16 displayState[]; // display shadow; halfword 0x2c holds the first window span word

// MakeCircleWindow (0x0202b620): builds the circle window: traces the circle with the midpoint algorithm into
// triangleTable (the radius of every scanline), spreads it into the span bank and stores the first span word in the
// display shadow.
void MakeCircleWindow(s16 centerX, s16 centerY, s16 radius) {
    s16 x;
    s16 y;
    s16 decision;
    s16 *table = triangleTable;

    MemClearFast(data_021352a0 + data_0212c4c8 * 0x180, 0x140);
    decision = 3 - radius * 2;
    y = radius;
    x = 0;
    if (radius >= 0) {
        do {
            table[x] = y;
            table[y] = x;
            if (decision < 0) {
                decision = decision + (s16)(x * 4 + 6);
                x++;
            } else {
                decision = decision + (s16)((x - y) * 4 + 10);
                y--;
                x++;
            }
        } while (y >= x);
    }
    make_circle_data(centerX, centerY, radius);
    displayState[0x2c] = *(u16 *)(data_021352a0 + data_0212c4c8 * 0x180);
}
