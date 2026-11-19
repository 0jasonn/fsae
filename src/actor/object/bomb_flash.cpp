#include "engine/functions.h"
#include "global.h"
#include "actor/object/bomb_flash.h"

// Bomb fuse flash: pulses the bomb's scale while the fuse is in its last 0x28 frames and blinks its palette.

typedef struct Vars_BombFlash {
    u8 unk_00[0x60];
    u32 flashPhase; // 0x60: pulse phase, moved by 0x10 per frame; bit 15 is the direction
} Vars_BombFlash;

extern KnifeObjAffineSrcData scrollArgs;

void bombFlash(Entity *e) {
    s32 blinkMask;
    s32 scale;

    if (e->subtimer > 0x28) {
        blinkMask = 8;
    } else {
        blinkMask = 4;
        if (VARS(Vars_BombFlash, e)->flashPhase & 0x8000) {
            VARS(Vars_BombFlash, e)->flashPhase -= 0x10;
        } else {
            VARS(Vars_BombFlash, e)->flashPhase += 0x10;
        }
        if ((VARS(Vars_BombFlash, e)->flashPhase & 0xf0) == 0 || (VARS(Vars_BombFlash, e)->flashPhase & 0xf0) > 0x80) {
            VARS(Vars_BombFlash, e)->flashPhase ^= 0x8000;
        }
        scale = 0x130 - (VARS(Vars_BombFlash, e)->flashPhase & 0xf0);
        ((s16 *)scrollArgs.data)[0] = scale;
        ((s16 *)scrollArgs.data)[1] = scale;
        ((s16 *)scrollArgs.data)[2] = 0;
        ObjAffineSet2(&scrollArgs, e);
    }
    if (e->subtimer & blinkMask) {
        e->spriteSettings.b16 = e->spriteSettings.b20;
    } else {
        e->spriteSettings.b16 = 0;
    }
}
