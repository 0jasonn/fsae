#include "engine/functions.h"
#include "global.h"
#include "object/objdecls_a.h"

extern u8 data_0212ceb0[];             // PlayerData array, byte flags at 0x39, 0xcd, 0x161, 0x1f5
extern u16 set33SpeedTable[];          // set33SpeedTable, per type
extern u8 set33Unk2eTable[];           // set33Unk2eTable, per type

// Actor fields of the Set33 family, file-local.
typedef struct Vars_Set33 {
    /* 00 */ u8 unk_00[0x68];
    /* 68 */ u16 savedX;
    /* 6a */ u16 savedY;
} Vars_Set33;

// set33_throw, 0x0206a8e4
ARM void set33_throw(Entity *e) {
    u8 nextAction;
    func_020847c8(e);
    func_0208af0c(e);
    if (!(e->layer & 0x8000)) {
        e->spriteSettings.b30 = 1;
        e->spriteSettings.b14 = e->spriteSettings.b30;
    }
    if (UpdateGravity(e, 0x1000)) {
        return;
    }
    nextAction = 4;
    e->action = nextAction;
    e->spriteSettings.b0 = 0;
    breakset(e);
    YureSet(0x1e, e->type);
}
