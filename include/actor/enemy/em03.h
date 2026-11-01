#ifndef UNKNOWN_A_BOSS_02038544_H
#define UNKNOWN_A_BOSS_02038544_H

#include "engine/entity.h"
#include "engine/player.h"

typedef struct Vars_02038544 {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *target; // player the actor aims at
    /* 68 */ u8 unk_68[4];
    /* 6c */ u16 unk_6c;
    /* 6e */ u8 unk_6e[0xe];
    /* 7c */ u8 savedUnk3f; // unk_3f value that em05_stop restores
    /* 7d */ u8 initHealth; // health when the actor was spawned
} Vars_02038544;
#define V(e) VARS(Vars_02038544, e)


extern const EntityFunc em03_noPartnerActions[];
extern const EntityFunc em03_normalActions[];
extern const u16 data_020d1820[];
extern const u8 em03_hitbox[];
extern const u8 em04_hitbox[];
extern const EntityFunc em04_normalActions[];
extern const EntityFunc em04_actions[];
extern const EntityFunc em05_actions[];
extern const u8 em05_hitbox[];
extern const EntityFunc *const em05_typeActions[];
extern u16 data_0212c58c[];
extern u8 data_0212ceb2[];
extern u8 data_0212ceca[];
extern u8 data_0212cee4[];
extern u16 frameCounter;
extern const s8 data_020d1844[];

#endif
