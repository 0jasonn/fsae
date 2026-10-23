#include "engine/functions.h"
#include "global.h"
#include "object/set3d.h"

// Set3d actor, third unit (module set3d). Address -> name:
//   0x0205d874 set3d_wait, 0x0205d898 set3d_back, 0x0205d8e4 settail (original name)
//   0x0205d9c8 set3d_setWaitOne (renamed from set3d_setWaitOne)

typedef struct Vars_Set3d {
    /* 00 */ u8 unk_00[0x1c];
    /* 1c */ u32 settingsWord; // sprite settings word, bit 2 is set by set3dyure
    /* 20 */ u8 unk_20[0x64 - 0x20];
    /* 64 */ u16 timer64;
    /* 66 */ u8 unk_66[2];
    /* 68 */ u32 waitCount;
} Vars_Set3d;

extern u32 data_0212c54c; // cleared by set3d_back

ARM void set3d_wait(Entity *e) {
    Vars_Set3d *vars = VARS(Vars_Set3d, e);
    u16 timer;

    timer = vars->timer64;
    vars->timer64 = timer - 1;
    if (timer == 0) {
        e->action = 2;
    }
    settail(e);
}

ARM void set3d_back(Entity *e) {
    if (e->timer != 0) {
        e->timer = e->timer - 1;
        settail(e);
        return;
    }
    data_0212c54c = 0;
    TelopRequest(0x44e);
    PutObjWork(e);
}

ARM Entity *settail(Entity *e) {
    Entity *child = 0;
    u8 prevSubtimer = e->subtimer;

    e->subtimer = prevSubtimer - 1;
    if (prevSubtimer == 0) {
        e->subtimer = 3;
        child = GetSetWork(0x3d, 1, 0);
        if (child != 0) {
            child->x.WORD = e->x.WORD;
            child->y.WORD = e->y.WORD;
            child->z.WORD = e->z.WORD;
        }
    }
    return child;
}
