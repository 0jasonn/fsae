#include "engine/functions.h"
#include "global.h"
#include "object/objdecls_a.h"

extern u8 rupeeKindTable[];             // rupee kind per random index (0xff = none)
extern const s8 rupeeOffsetTable[];       // per type: x and y offsets as s8 pairs (<< 16 when passed)
extern const s8 rupeeDirOffsetTable[];       // direction offsets, index is Random() & 7

// Actor fields of the rupee-spawning actor, file-local.
typedef struct Vars_Rupee {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u8 spawnBits;   // grows by one bit per spawn attempt
    /* 79 */ u8 unk_79;
    /* 7a */ u8 spawnCount;  // number of spawn attempts, at most 3
} Vars_Rupee;

// setrupee, 0x0206b4dc
ARM void setrupee(Entity *e) {
    Vars_Rupee *v = VARS(Vars_Rupee, e);
    u8 rupeeKind;
    Entity *found;
    if (v->spawnBits != 0) {
        rupeeKind = rupeeKindTable[Random() & 0xf];
    } else {
        rupeeKind = rupeeKindTable[Random() & 0x1f];
    }
    if (rupeeKind == 0xff) {
        if (v->spawnCount >= 3) {
            return;
        }
        v->spawnCount++;
        v->spawnBits = (v->spawnBits << 1) | 1;
        return;
    }
    found = GetSetWork(0, rupeeKind, 1);
    if (found == 0) {
        return;
    }
    ObjPosCopyOfs32(e, found, (s32)rupeeOffsetTable[e->type * 2] << 16, (s32)rupeeOffsetTable[e->type * 2 + 1] << 16);
    found->direction = (((s8)rupeeDirOffsetTable[Random() & 7] + ((e->type ^ 2) << 3)) & 0x1f) | 0x80;
}
