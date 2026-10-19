#ifndef UNKNOWN_WIP_A_BOSS_02039ED4_H
#define UNKNOWN_WIP_A_BOSS_02039ED4_H

#include "engine/entity.h"
#include "engine/player.h"

// Boss actor fields used by src/enemy/em09.c and its siblings. File-local overlay, not shared.
typedef struct Vars_BossDying {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u8 dying; // nonzero once the boss has started its death sequence
    /* 71 */ u8 unk_71[5];
    /* 76 */ u16 dyingTimer; // frames until explodeSet
} Vars_BossDying;
#define VBD(e) VARS(Vars_BossDying, e)

typedef struct Vars_BossLaunch {
    /* 00 */ u8 unk_00[0x74];
    /* 74 */ u16 launchTimer;
} Vars_BossLaunch;
#define VBL(e) VARS(Vars_BossLaunch, e)

typedef struct Vars_BossTarget {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u8 savedChildUnk2e; // child's unk_2e, saved when it latches on
    /* 79 */ u8 unk_79[3];
    /* 7c */ u8 latchTimer; // set to 0x2d when the actor latches onto a player
    /* 7d */ u8 savedPalette; // spriteSettings.b16 saved by em09_init
    /* 7e */ u16 savedAttr; // unk_20 (low byte) and spriteSettings.b6 (high byte)
} Vars_BossTarget;
#define VBT(e) VARS(Vars_BossTarget, e)

typedef struct Tbl3 {
    u8 v[3];
} Tbl3;

extern const EntityFunc em09_type2Actions[];
extern const u8 em09_paletteByType[];
extern const u8 em09_altPaletteA[];
extern const u8 em09_hitbox[];
extern const u16 data_0212c58c[];
extern Entity *data_0212c7d4[];
extern const s8 data_020d1d96[];
extern const s8 data_020d1d93[];
extern const u8 em09_altPaletteB[];
extern const EntityFunc em10_actions[];
extern const EntityFunc em10_normalActions[];
extern const u8 em10_hitbox[];
extern const u8 em10_awakeHitbox[];
extern const s8 em10_awakeSway[];
extern UnkStruct_0212c7c8 data_0212c7c8;
extern const u8 em09_hurtHitbox[];
extern const u16 em09_attrByChildType[];
extern const EntityFunc em09_noPartnerActions[];
extern const EntityFunc em09_normalActions[];
extern const s8 em09_purupuruSway[];


typedef struct UnkStruct_0212c648 {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 unk_18;
    /* 1a */ u16 unk_1a;
} UnkStruct_0212c648;
extern UnkStruct_0212c648 data_0212c648;
extern const u16 em11_blockMasks[];
extern const EntityFunc em11_actions[];
extern const EntityFunc em11_normalActions[];
extern const u8 em11_hitbox[];
extern const u8 em11_waitTimes[];
extern const EntityFunc em12_normalActions[];
extern const EntityFunc em12_actions[];

typedef struct Vars_BossCell {
    /* 00 */ u8 unk_00[0x7a];
    /* 7a */ u8 savedCell; // grid cell value saved when the boss claims its cell
} Vars_BossCell;
#define VBCELL(e) VARS(Vars_BossCell, e)

typedef struct Vars_BossPtr {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *target; // player the boss aims at
} Vars_BossPtr;
#define VBP(e) VARS(Vars_BossPtr, e)

typedef struct Vars_BossHalf {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u16 moveTimer; // counts down in em10_move until the actor switches state
} Vars_BossHalf;
#define VBH(e) VARS(Vars_BossHalf, e)

typedef struct Vars_ParentWord {
    /* 00 */ u8 unk_00[4];
    /* 04 */ s32 childAlive; // 0 means the linked child is removed
} Vars_ParentWord;
#define VPW(e) VARS(Vars_ParentWord, e)



#endif
