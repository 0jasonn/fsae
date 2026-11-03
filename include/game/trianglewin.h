#ifndef WIP_A_TRIANGLEWIN_H
#define WIP_A_TRIANGLEWIN_H

#include "engine/functions.h"
#include "engine/misc.h"
#include "engine/oam_ring.h"
#include "game/triangle.h"

extern const s16 data_020d7ed8[];   // sine table, 0x100 entries (angle 0..255)
extern const s16 trigTable[];       // cosine table
extern u8 hblankDma;                // window state, the span pointer is at +4

extern "C" {
void MakeTriangleWindow(s16 x, s16 y, s16 radius, s16 angle);   // 0x0202b828
}

#endif
