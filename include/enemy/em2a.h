#ifndef UNKNOWN_BOSS_02030A14_H
#define UNKNOWN_BOSS_02030A14_H

#include "engine/player.h"

typedef struct Vars_Boss {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ Entity *linked; // boss counter entity (em02_div) or PlayerData (func_02030ae4)
    /* 64 */ PlayerData *playerData;
    /* 68 */ u8 unk_68[8];
    /* 70 */ u16 waitTimer;
    /* 72 */ u8 savedAction;
    /* 73 */ u8 extraHop;
    /* 74 */ u8 hitLevel;
    /* 75 */ u8 hitWindow;
    /* 76 */ u8 unk_76[2];
    /* 78 */ u8 flashPlayer;
    /* 79 */ u8 shadowLandMask;
    /* 7a */ u8 unk_7a[2];
    /* 7c */ s32 effectTimer;
} Vars_Boss;
#define V(e) VARS(Vars_Boss, e)

// Hand-like child entity of the boss
typedef struct Vars_BossHand {
    /* 00 */ u8 unk_00[0x72];
    /* 72 */ u8 shadowStep;
    /* 73 */ u8 unk_73;
    /* 74 */ s16 targetX;
    /* 76 */ u16 targetY;
} Vars_BossHand;
#define VH(e) VARS(Vars_BossHand, e)

typedef struct Vars_Counter {
    /* 00 */ u8 unk_00[0x62];
    /* 62 */ u16 hitCount;
} Vars_Counter;

extern Entity *data_0212c648;
extern const u8 em2a_hitbox[];
extern const EntityFunc em2a_secondaryActions[];
extern const EntityFunc em2a_actions[];
extern const u8 em2a_subtimers[];
extern const u8 em2a_hitboxType1[];
extern const u8 em2a_hitboxType2[];
extern const u8 em2a_coreHitbox[];
extern const u16 em2a_wallMasks[];
extern const s8 em2a_shadowOffsets[];


#endif
