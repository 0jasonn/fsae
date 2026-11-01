#ifndef UNKNOWN_OBJECT_02033708_H
#define UNKNOWN_OBJECT_02033708_H

#include "engine/player.h"

// Event controller fields, see event_02033290.cpp
typedef struct Vars_Event {
    /* 00 */ u8 unk_00[0x7d];
    /* 7d */ u8 eventFlags;
} Vars_Event;
#define VE(e) VARS(Vars_Event, e)

typedef struct Vars_Lock {
    /* 00 */ u8 unk_00[0x6e];
    /* 6e */ u16 lockFlags;
    /* 70 */ u8 unk_70[0xc];
    /* 7c */ u16 lockValue;
    /* 7e */ u8 lockBitIndex;
} Vars_Lock;
#define VL(e) VARS(Vars_Lock, e)

typedef struct Vars_02033708 {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u16 homeX;
    /* 72 */ u8 pushProgress;
    /* 73 */ u8 unk_73;
    /* 74 */ u8 leverState;
    /* 75 */ u8 side; // 0 or 1
    /* 76 */ u8 lockBit;
    /* 77 */ u8 pushCount;
    /* 78 */ u8 unk_78[4];
    /* 7c */ Entity *lockEntity;
} Vars_02033708;
#define V(e) VARS(Vars_02033708, e)

extern const EntityFunc em2c_type1Actions[];
extern const s8 em2c_restXOffsets[];
extern const u8 data_020d0ef2[];
extern const u32 flagBits[];
extern const s8 em2c_liftOffsets[];
extern const s8 em2c_fxXOffsets[];
extern const u8 em2c_itemDrops[];
extern s32 em2c_leverTimers[];
extern s32 em2c_leverDone;


typedef struct Vars_Chain {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ Entity *chainA;
    /* 74 */ Entity *chainB;
    /* 78 */ Entity *chainC;
} Vars_Chain;
#define VC(e) VARS(Vars_Chain, e)

typedef struct Vars_Controller {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u8 chainBuilt;
    /* 7d */ u8 chainStep;
} Vars_Controller;
#define VCT(e) VARS(Vars_Controller, e)

extern const s16 trigTable[];

#endif
