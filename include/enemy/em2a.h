#ifndef UNKNOWN_BOSS_02030A14_H
#define UNKNOWN_BOSS_02030A14_H

#include "engine/player.h"

typedef struct Vars_Boss {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ Entity *unk_60;
    /* 64 */ PlayerData *unk_64;
    /* 68 */ u8 unk_68[8];
    /* 70 */ u16 unk_70;
    /* 72 */ u8 unk_72;
    /* 73 */ u8 unk_73;
    /* 74 */ u8 unk_74;
    /* 75 */ u8 unk_75;
    /* 76 */ u8 unk_76[2];
    /* 78 */ u8 unk_78;
    /* 79 */ u8 unk_79;
    /* 7a */ u8 unk_7a[2];
    /* 7c */ s32 unk_7c;
} Vars_Boss;
#define V(e) VARS(Vars_Boss, e)

// Hand-like child entity of the boss
typedef struct Vars_BossHand {
    /* 00 */ u8 unk_00[0x72];
    /* 72 */ u8 unk_72;
    /* 73 */ u8 unk_73;
    /* 74 */ s16 unk_74;
    /* 76 */ u16 unk_76;
} Vars_BossHand;
#define VH(e) VARS(Vars_BossHand, e)

typedef struct Vars_Counter {
    /* 00 */ u8 unk_00[0x62];
    /* 62 */ u16 unk_62;
} Vars_Counter;

extern Entity *data_0212c648;
extern const u8 data_020d0a62[];
extern const EntityFunc data_020d0a7c[];
extern const EntityFunc data_020d0dc0[];
extern const u8 data_020d0a42[];
extern const u8 data_020d0a52[];
extern const u8 data_020d0a72[];
extern const u8 data_020d0a4a[];
extern const u16 data_020d0a5a[];
extern const s8 data_020d0ab2[];


#endif
