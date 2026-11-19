#include "engine/functions.h"
#include "global.h"
#include "actor/object/set58.h"

// body_sazanami (0x020734a4): ripple spawner of the set58 body. Once bit 4 of the game flags is set a countdown runs;
// at fixed values of it a ripple object is created at the next (x, y) offset of set58_sazanamiOffsets, and at 0 the
// actor switches to action 2.
void body_sazanami(Entity *e) {
    Entity *ripple;
    if (!(em12_typeMasks[0] & 0x10)) {
        return;
    }
    if (V58(e)->unk_7c != 0) {
        V58(e)->unk_7c--;
    }
    switch (V58(e)->unk_7c) {
        case 0:
            e->action = 2;
            return;
        case 0x82:
        case 0x96:
        case 0xaa:
        case 0xd2:
        case 0x121:
            break;
        case 0x104:
            return;
        default:
            return;
    }
    ripple = GetSetWork(0x58, 6, 0);
    if (ripple == NULL) {
        return;
    }
    ObjPosCopyOfs32(e, ripple, set58_sazanamiOffsets[e->timer] << 16, set58_sazanamiOffsets[e->timer + 1] << 16);
    e->timer += 2;
}

