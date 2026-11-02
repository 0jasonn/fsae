#ifndef WIP_A_EM0C_3_H
#define WIP_A_EM0C_3_H

#include "engine/functions.h"
#include "engine/player.h"

// Sensor box of the em0c shooter (fields at 0x70.. of the entity).
typedef struct Em0cSensor {
    u8 unk_00[0x70];
    u16 boxX;       // 0x70: left edge of the box
    u16 boxY;       // 0x72: top edge of the box
    u8 unk_74[8];
    u16 boxWidth;   // 0x7c
    u16 boxHeight;  // 0x7e
} Em0cSensor;

BOOL areacheck(Entity *e);       // 0x0202c9a8
extern "C" BOOL areacheck2(Entity *e);   // 0x0202caa0
extern u8 frameCounter[];
extern "C" {
void em0c_shoot(Entity *e);      // 0x0202c80c
}

#endif
