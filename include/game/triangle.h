#ifndef GAME_TRIANGLE_H
#define GAME_TRIANGLE_H

#include "engine/functions.h"

// Radius table of the circle code and the edge table of the triangle code (triangleTable, 0x800 bytes up to
// data_02138fa0). MultiRoomInit clears it; FrameSet and PartsSet (scr_4.cpp) also use this address as the start of their
// u16 map work buffer, which runs past it (0x4000 bytes).
extern s16 triangleTable[0x400];
// Circle span bank (data_021352a0): 0x180 bytes per bank index, selected by data_0212c4c8.
extern u8 data_021352a0[];
#include "engine/vblank_request.h"

extern "C" {
void make_circle_data(s16 centerX, s16 centerY, s16 count);
void calc_triangle(s16 x0, s16 y0, s16 x1, s16 y1, s16 base);
}

#endif
