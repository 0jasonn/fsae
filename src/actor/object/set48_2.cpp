#include "engine/functions.h"
#include "global.h"
#include "actor/object/objdecls_a.h"
#include "actor/object/effectdecls.h"

extern u32 em12_typeMasks[];

typedef struct Vars_Set48 {
    u8 unk_00[0x52];
    u8 cellIndex;
    u8 unk_53[0xd];
    u32 typeMask;
    u8 unk_64[0x14];
    u32 savedBits;
    u32 otherBits;
} Vars_Set48;

void set48_move(Entity *e) {
    Vars_Set48 *v = VARS(Vars_Set48, e);
    u8 index;
    u32 mask;
    u32 bits;
    int bank;

    if ((e->contactFlags & 0x80) == 0) {
        return;
    }
    em12_typeMasks[v->cellIndex] ^= v->typeMask;
    if (v->typeMask & em12_typeMasks[v->cellIndex]) { bank = 0x8001; } else { bank = 0x8000; }
    e->spriteSettings.b16 = bank;
    e->iframes = 0xe8;
    EnqueueSFX(0x16);
}

