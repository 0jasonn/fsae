#include "engine/functions.h"
#include "global.h"
#include "actor/object/set43.h"

// 0x0206cea0 switchcheck (original name): tests the actor's type bits against em12_typeMasks of its area; the byte
// at 0x72 selects whether all bits set or not all bits set counts as a hit.

typedef struct Vars_Switch {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits;
    /* 64 */ u8 unk_64[0xe];
    /* 72 */ u8 inverted;
} Vars_Switch;

int switchcheck(Entity *e) {
    if (VARS(Vars_Switch, e)->inverted) {
        if (VARS(Vars_Switch, e)->typeBits != (VARS(Vars_Switch, e)->typeBits & em12_typeMasks[e->areaIndex])) {
            return TRUE;
        }
    } else {
        if (VARS(Vars_Switch, e)->typeBits == (VARS(Vars_Switch, e)->typeBits & em12_typeMasks[e->areaIndex])) {
            return TRUE;
        }
    }
    return FALSE;
}
