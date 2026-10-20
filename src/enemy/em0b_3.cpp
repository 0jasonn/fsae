#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "enemy/em00.h"

// Functions in this file (actor em0b, original names from the debug build):
//   em0b_return, trapAttBitCheck

// Return: when the check of the state is clear the action goes back two steps and the speed is doubled.
ARM void em0b_return(Entity *e) {
    if (func_020847a0(e) != 0) {
        return;
    }
    e->action -= 2;
    e->speed = e->speed << 1;
}

// Checks the two map points next to the entity (by the direction) for a trap; returns 1 when one of them blocks.
ARM BOOL trapAttBitCheck(Entity *e) {
    u8 index;
    u16 px;
    u16 py;
    s32 result;

    index = (e->direction >> 1) & 0xff;
    px = (u16)(e->x.HALF.HI + data_020cfdfc[index]);
    py = (u16)(e->y.HALF.HI + data_020cfdfc[index + 1]);
    result = func_02083d30((s16)px, (s16)py, e->layer);
    if ((py & 8) == 0) {
        result = (u8)(result >> 2);
    }
    if ((px & 8) == 0) {
        result = (u8)(result >> 1);
    }
    if (result & 1) {
        return 1;
    }
    px = (u16)(e->x.HALF.HI + data_020cfdfc[index + 2]);
    py = (u16)(e->y.HALF.HI + data_020cfdfc[index + 3]);
    result = func_02083d30((s16)px, (s16)py, e->layer);
    if ((py & 8) == 0) {
        result = (u8)(result >> 2);
    }
    if ((px & 8) == 0) {
        result = (u8)(result >> 1);
    }
    return result & 1;
}
