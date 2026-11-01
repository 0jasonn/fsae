#ifndef UNKNOWN_B_ACTOR_020407C8_H
#define UNKNOWN_B_ACTOR_020407C8_H

#include "engine/entity.h"
#include "engine/player.h"

typedef struct Vars_020407c8 {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *unk_64;
    /* 68 */ u8 unk_68[0x8];
    /* 70 */ u16 homeX;
    /* 72 */ u16 homeY;
    /* 74 */ u16 resetVal0;   // copied to the bubble by BubbleReset
    /* 76 */ u16 resetVal1;
    /* 78 */ u16 resetVal2;
    /* 7a */ u16 resetVal3;
    /* 7c */ u16 resetTimer;  // set to 0x258 by BubbleReset
    /* 7e */ u16 lifeTimer;   // counts down; the bubble is removed at 0
} Vars_020407c8;
#define V(e) VARS(Vars_020407c8, e)

extern const EntityFunc em26_mainTable[];
extern const EntityFunc em26_normalTable[];
extern const u8 data_020d31a0[];
extern const EntityFunc em27_mainTable[];
extern const EntityFunc em27_normalTable[];
extern const u8 data_020d3224[];
extern const EntityFunc em27_handlerTable[];
extern const u8 em28_hitbox[];

typedef struct UnkStruct_021348cc {
    s32 claimed;
    s32 unk_4;
} UnkStruct_021348cc;
extern UnkStruct_021348cc em28_claim;

u8 func_02084a30(Entity *e);

void BubbleReset(Entity *e);
void childInit(Entity *e, Entity *other);

#endif
