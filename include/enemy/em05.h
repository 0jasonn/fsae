#ifndef UNKNOWN_A_BOSS_02039074_H
#define UNKNOWN_A_BOSS_02039074_H

#include "enemy/em03.h"

// Actor fields for src/enemy/em05_4.c. File-local overlay, not shared.
typedef struct Vars_02039074 {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *target; // player the boss aims at
    /* 68 */ u8 unk_68[9];
    /* 71 */ u8 mirroredAnim; // animation copied from the player entity
    /* 72 */ u8 poseLatched;
    /* 73 */ u8 flashTimer;
    /* 74 */ u16 launchTimer;
    /* 76 */ u16 dyingTimer;
    /* 78 */ u8 jumpPhase;
    /* 79 */ u8 unk_79[3];
    /* 7c */ u8 lastHealth; // health seen at the last hit check
    /* 7d */ u8 healthBackup; // health restored after a jump
    /* 7e */ u16 jumpTimer;
} Vars_02039074;
#define VB(e) VARS(Vars_02039074, e)

// Halfword at 0x62 of the entity referenced by unk_60 (guess: count of split pieces)
typedef struct Vars_Target {
    /* 00 */ u8 unk_00[0x62];
    /* 62 */ u16 pieceCount;
} Vars_Target;



extern const EntityFunc data_020d1b94[];
extern const EntityFunc data_020d1b84[];
extern const EntityFunc data_020d1c20[];
extern const EntityFunc data_020d1c7c[];
extern const EntityFunc data_020d1a64[];
extern const EntityFunc data_020d1d40[];
extern const EntityFunc data_020d1d58[];
extern const EntityFunc data_020d1d2c[];
extern const u8 data_020d1b8c[];
extern const u8 data_020d1bcc[];
extern const u8 data_020d1bd4[];
extern const u8 data_020d1cd4[];
extern const u8 data_020d1cdc[];
extern const s8 data_020d1b7c[];
extern const s8 data_020d1998[];
extern const u16 data_020d1ccc[];
extern u16 data_0212c540[];

#endif
