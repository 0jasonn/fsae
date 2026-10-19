#ifndef UNKNOWN_OBJECT_02033708_H
#define UNKNOWN_OBJECT_02033708_H

#include "engine/player.h"

// Event controller fields, see event_02033290.cpp
typedef struct Vars_Event {
    /* 00 */ u8 unk_00[0x7d];
    /* 7d */ u8 unk_7d;
} Vars_Event;
#define VE(e) VARS(Vars_Event, e)

typedef struct Vars_Lock {
    /* 00 */ u8 unk_00[0x6e];
    /* 6e */ u16 unk_6e;
    /* 70 */ u8 unk_70[0xc];
    /* 7c */ u16 unk_7c;
    /* 7e */ u8 unk_7e;
} Vars_Lock;
#define VL(e) VARS(Vars_Lock, e)

typedef struct Vars_02033708 {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u16 unk_70;
    /* 72 */ u8 unk_72;
    /* 73 */ u8 unk_73;
    /* 74 */ u8 unk_74;
    /* 75 */ u8 unk_75; // side
    /* 76 */ u8 unk_76;
    /* 77 */ u8 unk_77;
    /* 78 */ u8 unk_78[4];
    /* 7c */ Entity *unk_7c;
} Vars_02033708;
#define V(e) VARS(Vars_02033708, e)

extern const EntityFunc data_020d101c[];
extern const s8 data_020d0eba[];
extern const u8 data_020d0ef2[];
extern const u32 data_020cf9b8[];
extern const s8 data_020d0f0a[];
extern const s8 data_020d0ec0[];
extern const u8 data_020d0f02[];
extern s32 data_021348b8[];
extern s32 data_021348b4;


typedef struct Vars_Chain {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ Entity *unk_70;
    /* 74 */ Entity *unk_74;
    /* 78 */ Entity *unk_78;
} Vars_Chain;
#define VC(e) VARS(Vars_Chain, e)

typedef struct Vars_Controller {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u8 unk_7c;
    /* 7d */ u8 unk_7d;
} Vars_Controller;
#define VCT(e) VARS(Vars_Controller, e)

extern const s16 data_020d7e58[];

#endif
