#include "engine/functions.h"
#include "global.h"
#include "object/objdecls_f.h"

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
    /* 10 */ u16 windowA;    // first argument of InitCircleWindow, high byte taken from data_0212c75c
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

// data_0212c648 as read by zfade_move: scroll origin of the camera.
typedef struct ZfadeCamera {
    /* 00 */ Entity *target;
    /* 04 */ u8 unk_04[0x1c];
    /* 20 */ s16 scrollX;
    /* 22 */ s16 scrollY;
} ZfadeCamera;

// Fade work at data_0212c5ac, only the fields read here.
typedef struct ZfadeFade {
    /* 00 */ u8 unk_00[3];
    /* 03 */ u8 blendStep;
    /* 04 */ u8 unk_04[4];
    /* 08 */ s16 blendWeight;
} ZfadeFade;

// data_0212c75c as read by zfade_init: only the high byte of the halfword at 0x60 is used.
typedef struct ZfadeScreen {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u16 fadeMask;
} ZfadeScreen;

extern const ZfadeEntry zfadeTable[];        // zeldaFadeTable, indexed by e->type
extern ZfadeCamera data_0212c648;
extern ZfadeFade data_0212c5ac;
extern ZfadeScreen data_0212c75c;
extern u8 data_02171d1c;                     // 1 while no fade partner is active
extern const EntityFunc zfade_typeHandlers[]; // zfade_typeHandlers, indexed by e->type

void zfade_move(Entity *e);

ARM void zfadeDispatch(Entity *e) {
    zfade_typeHandlers[e->type](e);
}
