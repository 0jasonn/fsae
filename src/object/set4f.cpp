#include "engine/functions.h"
#include "global.h"

// Set4f actor (module set4f). Address -> name:
//   0x0205e87c Set4f (original name, state table set4f_states indexed by e->action)
//   0x0205e898 set4f_init (original name)
//   0x0205e8f8 set4f_wait (original name)
//   0x0205e914 set4f_move (original name, parked in scratch/agentC/nonmatching)

typedef struct ScrollOrigin_Set4f {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 scrollX;
    /* 1a */ u16 scrollY;
} ScrollOrigin_Set4f;

extern ScrollOrigin_Set4f data_0212c648; // scroll origin of the current map
extern const EntityFunc set4f_states[]; // state table indexed by e->action
extern u16 set4f_rewriteIds[]; // RewCell id per actor type

typedef struct Vars_Set4f {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u8 lastState; // value of *statePtr last time it changed
    /* 79 */ u8 rewritePending; // set while the cell is being rewritten
    /* 7a */ u16 cell; // cell position from the actor's x/y
    /* 7c */ u8 *statePtr; // byte in the background buffer that drives this actor
} Vars_Set4f;

ARM void Set4f(Entity *e) {
    set4f_states[e->action](e);
}

ARM void set4f_init(Entity *e) {
    Vars_Set4f *v = VARS(Vars_Set4f, e);
    s32 base;

    e->action = 1;
    base = GetBgBuffAdrs(e->layer);
    v->cell = (u16)(((e->x.HALF.HI - data_0212c648.scrollX) >> 4) |
                    (((e->y.HALF.HI - data_0212c648.scrollY) >> 4) << 6));
    v->statePtr = (u8 *)(base + 4 + 0x2000 + v->cell);
}

ARM void set4f_wait(Entity *e) {
    Vars_Set4f *v = VARS(Vars_Set4f, e);
    u8 state = *v->statePtr;

    if (state != 0) {
        v->lastState = state;
        e->action = 2;
    }
}
