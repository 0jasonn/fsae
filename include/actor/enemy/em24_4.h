#ifndef WIP_B_EM24_4_H
#define WIP_B_EM24_4_H

#include "engine/functions.h"

extern u16 frameCounter;                 // frame counter (frameCounter)
extern const s8 fuwafuwaTable[];         // fuwafuwaTable, z offset of fuwafuwa, indexed by (frameCounter + subtimer) & 0xf >> 2

#endif
