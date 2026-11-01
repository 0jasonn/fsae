#ifndef WIP_B_TRIANGLE_H
#define WIP_B_TRIANGLE_H

#include "engine/functions.h"

// Radius table of the circle code and the edge table of the triangle code (triangleTable, bss, only used by these
// functions).
extern s16 triangleTable[];
// Circle span bank (data_021352a0): 0x180 bytes per bank index, selected by data_0212c4c8.
extern u8 data_021352a0[];
extern u8 data_0212c4c8;

extern "C" {
void make_circle_data(s16 centerX, s16 centerY, s16 count);
void calc_triangle(s16 x0, s16 y0, s16 x1, s16 y1, s16 base);
}

#endif
