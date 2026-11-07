#include "engine/functions.h"
#include "global.h"
#include "actor/object/objdecls_a.h"
#include "actor/object/effectdecls.h"

extern u8 playerWork[];             // PlayerData array, byte flags at 0x39, 0xcd, 0x161, 0x1f5
extern u16 set33SpeedTable[];          // set33SpeedTable, per type
extern u8 set33Unk2eTable[];           // set33Unk2eTable, per type

// Actor fields of the Set33 family, file-local.
typedef struct Vars_Set33 {
    /* 00 */ u8 unk_00[0x68];
    /* 68 */ u16 savedX;
    /* 6a */ u16 savedY;
} Vars_Set33;

// set33_liftup, 0x0206a7b8
// set33_liftup, 0x0206a7b8
void set33_liftup(Entity *e) {
    Vars_Set33 *v = VARS(Vars_Set33, e);
    Entity *found;
    u8 subtimer;
    s32 z;
    MoveDir(e);
    e->z.WORD -= 0x8000;
    e->subtimer--;
    if (e->subtimer != 0) { return; }
    e->action = 2;
    e->x.HALF.HI = v->savedX;
    e->y.HALF.HI = v->savedY;
    e->z.HALF.HI = 2 - 0x12;
    found = GetSetWork(0xf, (u8)(e->type + 8), 0);
    if (found == 0) {
        return;
    }
    ObjPosCopy(e, found);
}
