#include "engine/functions.h"
#include "global.h"
#include "object/c_decls.h"

// Set5c actor, init and states (module set5c). Address -> name:
//   0x0205f9d4 set5c_init (name from symbols.txt)
//   0x0205fa50 set5c_block_set (name from symbols.txt)
//   0x0205fa8c set5c_appear (name from symbols.txt)
//   (set5c_vanish at 0x0205fadc is parked in scratch/agentC/nonmatching)
//   (set5c_update at 0x0205fb38 is in the next unit)

// Actor fields past the shared header
typedef struct Vars_Set5c {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeMask; // ParseTypeBits(type), tested against em12_typeMasks[area]
    /* 64 */ u32 typeMask2; // ParseTypeBits(type2), tested by set5c_vanish
    /* 68 */ s32 cell; // cell index of the actor's position
} Vars_Set5c;

extern u32 em12_typeMasks[]; // one mask per area

void set5c_block_set(Entity *e);

ARM void set5c_init(Entity *e) {
    Vars_Set5c *v = VARS(Vars_Set5c, e);

    e->action = e->action + 1;
    v->typeMask = ParseTypeBits(e->type);
    v->typeMask2 = ParseTypeBits(e->type2);
    v->cell = MAP_CELL_INDEX(e->x.HALF.HI, e->y.HALF.HI);
    if (e->type != 0xff) {
        return;
    }
    set5c_block_set(e);
    e->action = 2;
}

ARM void set5c_block_set(Entity *e) {
    Vars_Set5c *v = VARS(Vars_Set5c, e);

    if (func_0208583c()) {
        KemuriSet(e);
    }
    RewCellOne(0x136, (u16)v->cell, e->layer);
}

ARM void set5c_appear(Entity *e) {
    Vars_Set5c *v = VARS(Vars_Set5c, e);

    if (v->typeMask != (v->typeMask & em12_typeMasks[e->areaIndex])) {
        return;
    }
    set5c_block_set(e);
    e->action = e->action + 1;
    if (e->type2 != 0xff) {
        return;
    }
    PutObjWork(e);
}
