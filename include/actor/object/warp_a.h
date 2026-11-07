#ifndef WIP_A_WARP_A_H
#define WIP_A_WARP_A_H

#include "engine/functions.h"
#include "engine/player.h"
#include "knife/comm/singleplay_warp_api.h"

// First 0x80 bytes of an Entity (the part the SinglePlay warp code saves and restores)
typedef struct EntityHead {
    /* 00 */ u32 link0;
    /* 04 */ u32 link1;
    /* 08 */ u8 objKind;
    /* 09 */ u8 objId;
    /* 0a */ u8 type;
    /* 0b */ u8 type2;
    /* 0c */ s32 speed;
    /* 10 */ s32 zVelocity;
    /* 14 */ u8 action;
    /* 15 */ u8 subAction;
    /* 16 */ u8 unk_16;
    /* 17 */ u8 timer;
    /* 18 */ u8 subtimer;
    /* 19 */ u8 unk_19;
    /* 1a */ u8 unk_1a;
    /* 1b */ u8 unk_1b;
    /* 1c */ u32 spriteWord;
    /* 20 */ u8 unk_20;
    /* 21 */ u8 unk_21;
    /* 22 */ u8 unk_22;
    /* 23 */ u8 unk_23;
    /* 24 */ u32 unk_24;
    /* 28 */ u8 unk_28;
    /* 29 */ u8 frame;
    /* 2a */ u8 animationState;
    /* 2b */ u8 direction;
    /* 2c */ u16 wallFlags;
    /* 2e */ u8 unk_2e;
    /* 2f */ u8 unk_2f;
    /* 30 */ s32 x;
    /* 34 */ s32 y;
    /* 38 */ s32 z;
    /* 3c */ u8 statusFlags;
    /* 3d */ u8 iframes;
    /* 3e */ u8 baseDirection;
    /* 3f */ u8 poseId;
    /* 40 */ u8 unk_40;
    /* 41 */ u8 contactFlags;
    /* 42 */ u8 unk_42;
    /* 43 */ u8 unk_43;
    /* 44 */ u8 attackDamage;
    /* 45 */ u8 health;
    /* 46 */ u8 attackKnockback;
    /* 47 */ u8 unk_47;
    /* 48 */ const void *hitbox;
    /* 4c */ Entity *contactedEntity;
    /* 50 */ u16 layer;
    /* 52 */ u8 areaIndex;
    /* 53 */ u8 unk_53;
    /* 54 */ Entity *parent;
    /* 58 */ Entity *child;
    /* 5c */ u16 unk_5c;
    /* 5e */ u8 unk_5e;
    /* 5f */ u8 unk_5f;
    /* 60 */ u32 rest[8];
} EntityHead;

// First bytes of the SinglePlay instance
typedef struct SinglePlayWarpHead {
    /* 00 */ u8 contNo;
    /* 01 */ u8 unk_01[4];
    /* 05 */ u8 unk_05;
    /* 06 */ u8 unk_06[6];
    /* 0c */ u8 unk_0c;
    /* 0d */ u8 playerMask;
} SinglePlayWarpHead;

extern "C" {
BOOL Knife_Single_SinglePlay_CheckShell(void *self, Entity *e, int a);
void Knife_Single_SinglePlay_InitializeFormation(void *self);
BOOL Knife_Single_SinglePlay_WarpPartner(void *self, PlayerData *player0, PlayerData *player1);
BOOL Knife_Single_SinglePlay_WarpPartnerToTarget(void *self, PlayerData *player0, PlayerData *player1, s16 x, s16 y);
int func_02083d30(s16 x, s16 y, u16 layer);  // thumb, cell class at a map position
}
int func_02083d18(Entity *e, int dx, int dy);  // thumb, cell class at an offset of the entity
int func_02083c74(Entity *e, int dx, int dy);  // thumb, cell kind at an offset of the entity

// Bit view of PlayerData::paletteBits (0x8b): b = bits 2..3 (palette index)
typedef struct PalBits {
    u8 a : 2;
    u8 b : 2;
    u8 c : 3;
    u8 d : 1;
} PalBits;

#endif
