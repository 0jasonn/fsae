#ifndef UNKNOWN_B_ACTOR_020407C8_H
#define UNKNOWN_B_ACTOR_020407C8_H

#include "engine/entity.h"
#include "engine/player.h"

typedef struct Vars_020407c8 {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *unk_64;
    /* 68 */ u8 unk_68[0x8];
    /* 70 */ u16 unk_70;
    /* 72 */ u16 unk_72;
    /* 74 */ u16 unk_74;
    /* 76 */ u16 unk_76;
    /* 78 */ u16 unk_78;
    /* 7a */ u16 unk_7a;
    /* 7c */ u16 unk_7c;
    /* 7e */ u16 unk_7e;
} Vars_020407c8;
#define V(e) VARS(Vars_020407c8, e)

extern const EntityFunc data_020d31b8[];
extern const EntityFunc data_020d31a8[];
extern const u8 data_020d31a0[];
extern const EntityFunc data_020d322c[];
extern const EntityFunc data_020d321c[];
extern const u8 data_020d3224[];
extern const EntityFunc data_020d3334[];
extern const u8 data_020d32d4[];

typedef struct UnkStruct_021348cc {
    s32 unk_0;
    s32 unk_4;
} UnkStruct_021348cc;
extern UnkStruct_021348cc data_021348cc;

u8 func_02084a30(Entity *e);

void BubbleReset(Entity *e);
void childInit(Entity *e, Entity *other);

#endif
