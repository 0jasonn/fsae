#ifndef UNKNOWN_WIP_F_COIN_H
#define UNKNOWN_WIP_F_COIN_H

#include "object/setcommon.h"

// Coin / kirakira actor fields (file-local overlay for src/object/coin.cpp, not shared).
typedef struct Vars_Coin {
    /* 00 */ u8 unk_00[0x1c];
    /* 1c */ u32 spriteWord; // Entity.spriteSettings as one word
} Vars_Coin;
#define VCOIN(e) VARS(Vars_Coin, e)

extern const EntityFunc coin_actions[];   // coin_actions, indexed by e->action
extern u16 data_0212c594;                 // frame counter used by the sparkle and blink code
void kirakira_set(Entity *e);

#endif
