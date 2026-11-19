#include "engine/functions.h"
#include "global.h"
#include "engine/blend_request.h"
#include "actor/object/objdecls_f.h"

// Zelda fade window (module zfade). Address -> name:
//   zfade_init (0x0205b768) and zfade_move (0x0205b800): scratch/agentF/nonmatching/zfade_init.c, zfade_move.c
//   0x0205b988 zfadeDispatch (dsd name zfadeDispatch), dispatches on e->type through zfade_typeHandlers

// One 0x14-byte record per type in zeldaFadeTable, all halfwords.
typedef struct ZfadeEntry {
    /* 00 */ u16 unk_00;
    /* 02 */ u16 unk_02;
    /* 04 */ u16 start;      // start value of the phase and the duration
    /* 06 */ u16 velocity;   // initial velocity
    /* 08 */ u16 accel;      // velocity change per frame
    /* 0a */ u16 accumInit;  // initial accumulator
    /* 0c */ u16 vel2Init;   // initial second velocity
    /* 0e */ u16 accel2Init; // second velocity change per frame
    /* 10 */ u16 windowA;    // first argument of InitCircleWindow, high byte taken from displayState
    /* 12 */ u16 windowB;
} ZfadeEntry;

typedef struct Vars_Zfade {
    /* 00 */ u8 unk_00[0x76];
    /* 76 */ s16 duration;   // divisor of the blend step
    /* 78 */ u8 unk_78;
    /* 79 */ s8 accel2;      // per-frame change of vel2
    /* 7a */ s8 vel2;        // second velocity
    /* 7b */ u8 accum;       // accumulates vel2, passed to MakeTriangleWindow
    /* 7c */ s8 accel;       // per-frame change of vel
    /* 7d */ s8 vel;         // velocity
    /* 7e */ s16 phase;      // counts from the start value, 0x1f4 is the upper limit
} Vars_Zfade;

extern const ZfadeEntry zfadeTable[];        // zeldaFadeTable, indexed by e->type
#include "engine/map_state.h"
extern u8 data_02171d1c;                     // 1 while no fade partner is active
extern const EntityFunc zfade_typeHandlers[]; // zfade_typeHandlers, indexed by e->type

void zfade_move(Entity *e);

void zfadeDispatch(Entity *e) {
    zfade_typeHandlers[e->type](e);
}
