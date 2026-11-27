#include "engine/functions.h"
#include "game/triangle.h"
#include "engine/irq.h"

// make_circle_data(short, short, short), 0x0202b72c: fills the current span bank (data_021352a0, bank data_0212c4c8)
// for the rows around centerY: each step takes the next half width from triangleTable and writes the right and left
// edge of the circle (clamped to 0..0xff) into the row below and the row above, skipping rows outside the 0xc0
// visible lines. Then points the HBlank DMA source at the bank.
void make_circle_data(s16 centerX, s16 centerY, s16 count) {
    s16 half;
    s16 upY;
    u8 *rowUp;
    u8 *rowDown;
    s16 *table;
    s16 left;
    s16 right;

    rowDown = data_021352a0 + data_0212c4c8 * 0x180 + centerY * 2;
    rowUp = rowDown;
    upY = centerY;
    table = triangleTable;

    while (count-- != 0) {
        half = *table++;
        left = centerX - half;
        right = centerX + half;
        if (left < 0) {
            left = 0;
        }
        if (right >= 0xff) {
            right = 0xff;
        }
        if ((u16)upY < 0xc0) {
            rowUp[0] = right;
            rowUp[1] = left;
        }
        if ((u16)centerY < 0xc0) {
            rowDown[0] = right;
            rowDown[1] = left;
        }
        upY--;
        rowUp -= 2;
        rowDown += 2;
        centerY++;
    }
    hblankDma.src = data_021352a0 + data_0212c4c8 * 0x180 + 2;
}
