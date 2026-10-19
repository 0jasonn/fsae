#ifndef UNKNOWN_BOSS_02036CA4_H
#define UNKNOWN_BOSS_02036CA4_H

#include "engine/player.h"

typedef struct Vars_02036ca4 {
    /* 00 */ u8 unk_00[0x6e];
    /* 6e */ u16 attackCounter;
    /* 70 */ u8 subPhase;
    /* 71 */ u8 tsubomiSlot;
    /* 72 */ u8 stormTimer;
    /* 73 */ u8 unk_73;
    /* 74 */ const u16 *pathCursor; // path
    /* 78 */ u16 targetX; // target x
    /* 7a */ u16 targetY; // target y
    /* 7c */ u8 attackSeed; // attack history
    /* 7d */ s8 stormDir;
    /* 7e */ u8 pathWait;
} Vars_02036ca4;
#define V(e) VARS(Vars_02036ca4, e)

typedef struct UnkStruct_0212c5ac {
    /* 00 */ u8 unk_00[7];
    /* 07 */ u8 unk_7;
    /* 08 */ u8 unk_8[4];
    /* 0c */ s32 unk_c;
} UnkStruct_0212c5ac;
extern UnkStruct_0212c5ac data_0212c5ac;
extern Entity *data_0212c648;
extern u8 messageRequest;
extern const EntityFunc em2f_actions[];
extern const u8 em2f_hitbox[];
extern const u8 em2f_healthByDifficulty[];
extern const u8 em2f_mapData[];
extern s32 em2f_mapFlag;
extern u8 localPlayerIndex;
extern u8 data_0212c618;
extern const u16 em2f_tsubomiSpeeds[];
extern const u32 flagBits[];
extern const s16 trigTable[];
extern const u8 em2f_fiveAttackCounts[];
extern u16 data_0212c5bc;
extern const u8 em2f_slotNext[][8];
extern const u16 *const em2f_tsubomiPaths[];
extern const u8 em2f_moveGateMasks[];
extern const u8 data_020d1458[];
extern const u16 *const em2f_stormPaths[];
extern const u16 *const em2f_fivePaths[];
extern const u8 em2f_vitalThresholds[][2];


#endif
