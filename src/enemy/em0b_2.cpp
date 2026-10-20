#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "enemy/em00.h"

// Functions in this file (actor em0b, original name em0b_wait)

// Wait: when the input bit is set, the direction is taken from the input and the position of the target is stored.
ARM void em0b_wait(Entity *e) {
    u32 input;

    input = func_02084ac8(e, 10);
    if ((input & 0x80) == 0) {
        return;
    }
    e->direction = input & 0x18;
    if (trapAttBitCheck(e) != 0) {
        return;
    }
    switch (e->direction >> 3) {
    case 0:
        *(s16 *)((u8 *)e + 0x7c) = e->y.HALF.HI - (e->timer << 3);
        break;
    case 1:
        *(s16 *)((u8 *)e + 0x7c) = e->x.HALF.HI + (e->timer << 3);
        break;
    case 2:
        *(s16 *)((u8 *)e + 0x7c) = e->y.HALF.HI + (e->timer << 3);
        break;
    case 3:
        *(s16 *)((u8 *)e + 0x7c) = e->x.HALF.HI - (e->timer << 3);
        break;
    }
    u8 action;

    action = e->action;
    *(s32 *)((u8 *)e + 0x78) = 0;
    e->action = action + 1;
}
