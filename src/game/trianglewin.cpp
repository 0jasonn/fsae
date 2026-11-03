#include "engine/functions.h"
#include "game/trianglewin.h"

// MakeTriangleWindow(x, y, radius, angle) (0x0202b828): builds the triangle window. The three corners lie on the circle
// of the given radius around (x, y), 0x68 / 0xe8 / 0x40 angle steps apart. The edges are traced into triangleTable
// (calc_triangle), then every scanline's three values are sorted and the span (right edge, left edge) is written into the
// span bank selected by data_0212c4c8. The first span word goes to the window register shadow and the bank to the
// horizontal blank DMA.
void MakeTriangleWindow(s16 x, s16 y, s16 radius, s16 angle) {
    int a;
    int x0;
    u8 *span;
    int x1;
    int x2;
    int y0;
    int count;
    int tmp;
    int y2;
    int lo;
    int y1;
    s16 *src;
    int b;
    int c;

    MIi_CpuClear16(0xffff, triangleTable, 0x480);
    x0 = x + ((radius * data_020d7ed8[(angle - 0x40) & 0xff]) >> 8);
    y0 = y + ((radius * trigTable[(angle - 0x40) & 0xff]) >> 8);
    x1 = x + ((radius * data_020d7ed8[(angle + 0x68) & 0xff]) >> 8);
    y1 = y + ((radius * trigTable[(angle + 0x68) & 0xff]) >> 8);
    x2 = x + ((radius * data_020d7ed8[(angle - 0xe8) & 0xff]) >> 8);
    y2 = y + ((radius * trigTable[(angle - 0xe8) & 0xff]) >> 8);
    calc_triangle(x0, y0, x1, y1, 0);
    calc_triangle(x0, y0, x2, y2, 1);
    calc_triangle(x1, y1, x2, y2, 2);
    func_02029a50(data_021352a0 + data_0212c4c8 * 0x180, 0x180);
    span = data_021352a0 + data_0212c4c8 * 0x180;
    src = triangleTable;
    for (count = 0xc0; count > 0; count--) {
        a = *src++;
        b = *src++;
        c = *src++;
        lo = a;
        if (a > b) {
            lo = b;
            b = a;
        }
        if (lo > c) {
            tmp = lo;
            lo = c;
            c = tmp;
        }
        if (b > c) {
            tmp = b;
            b = c;
            c = tmp;
        }
        if (lo != -1) {
            span[0] = c;
            span[1] = lo;
        } else if (b != -1) {
            span[0] = c;
            span[1] = b;
        } else if (c != -1) {
            span[0] = span[1] = lo;
        }
        span += 2;
    }
    *(u16 *)&data_0212c75c.unk_32[0x26] = *(u16 *)(data_021352a0 + data_0212c4c8 * 0x180);
    *(u8 **)(&hblankDma + 4) = data_021352a0 + data_0212c4c8 * 0x180;
    DC_FlushRange(data_021352a0 + data_0212c4c8 * 0x180, 0x180);
}
