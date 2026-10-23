#include "engine/functions.h"
#include "global.h"
#include "object/set3d.h"

// Set3d actor (module set3d). Address -> name:
//   0x0205ceec Set3d (original name)
//   (set3d_init at 0x0205cfac is in scratch/agentF/nonmatching; set3dyure at 0x0205d940 is too)

extern const EntityFunc data_020d8c24[]; // state table indexed by e->action

typedef struct Vars_Set3d {
    /* 00 */ u8 unk_00[0x68];
    /* 68 */ u32 waitCount;
} Vars_Set3d;

ARM void Set3d(Entity *e) {
    u32 b14;
    u32 b30;

    data_020d8c24[e->action](e);
    if (e->type == 0) {
        b14 = e->spriteSettings.b14;
        b30 = e->spriteSettings.b30;
        func_0208ae30(e);
        e->spriteSettings.b14 = b14;
        e->spriteSettings.b30 = b30;
    }
    if (e->type != 0) {
        return;
    }
    if (e->action == 1 || e->action == 5) {
        return;
    }
    set3dyure(e);
    if (VARS(Vars_Set3d, e)->waitCount-- == 0) {
        SoundReq(0x4c);
        e->timer = 0x40;
        e->action = 5;
        e->spriteSettings.b0 = 1;
    }
}
