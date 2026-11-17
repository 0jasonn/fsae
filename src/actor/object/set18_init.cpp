#include "engine/functions.h"
#include "actor/object/pot.h"

// Entity overlay of the set18 actor.
typedef struct Vars_Set18 {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits;   // ParseTypeBits(type2) of the flags this actor waits for, 0 when none
    /* 64 */ u8 unk_64[0x18];
    /* 7c */ u16 *cell;      // BG cell under the actor
} Vars_Set18;
#define V18(e) VARS(Vars_Set18, e)

// set18_init, 0x02065650. Remembers the BG cell under the actor; bit 7 of the type marks an actor that waits for
// the flags named by type2 (kept in subtimer / typeBits), the low bits stay as the type.
void set18_init(Entity *e) {
    e->action++;
    u8 *bg = (u8 *)GetBgBuffAdrs(e->layer);
    V18(e)->cell = (u16 *)(bg + 4 + MAP_CELL_INDEX(e->x.HALF.HI, e->y.HALF.HI) * 2);
    e->subtimer = e->type & 0x80;
    e->type &= 0x1f;
    V18(e)->typeBits = e->subtimer ? ParseTypeBits(e->type2) : 0;
}
