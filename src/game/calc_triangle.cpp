#include "engine/functions.h"
#include "game/triangle.h"

// calc_triangle(short, short, short, short, short), 0x0202ba58: traces one edge of a triangle from (x0, y0) to (x1, y1)
// into triangleTable (three entries per scanline, base selects the entry) with a 16.16 step, clamping the rows to
// 0..0xbf and the x values to 0..0xff. Edges completely above or below the screen and flat edges are skipped.
void calc_triangle(s16 x0, s16 y0, s16 x1, s16 y1, s16 base) {
    s32 step;
    s16 *table;
    s16 swapY;
    s16 x;
    s32 position;
    s16 swapX;

    table = triangleTable;
    if (y0 < 0) {
        if (y1 < 0) {
            return;
        }
    }
    if (y0 > 0xbf) {
        if (y1 > 0xbf) {
            return;
        }
    }
    if (y0 > y1) {
        swapY = y0;
        swapX = x0;
        y0 = y1;
        x0 = x1;
        y1 = swapY;
        x1 = swapX;
    }
    if (y0 == y1) {
        return;
    }
    step = ((x1 - x0) << 16) / (y1 - y0);
    if (y0 < 0) {
        x0 = x0 + (s16)((-y0 * step) >> 16);
        y0 = 0;
    }
    if (y1 > 0xbf) {
        y1 = 0xbf;
    }
    x = x0;
    table += base + y0 * 3;
    position = x0 << 16;
    do {
        position += step;
        if (x < 0) {
            x = 0;
        }
        if (x > 0xff) {
            x = 0xff;
        }
        *table = x;
        table += 3;
        x = position >> 16;
        y0++;
    } while (y1 >= y0);
}
