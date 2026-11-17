#ifndef ACTOR_ENEMY_EM0B_INIT_H
#define ACTOR_ENEMY_EM0B_INIT_H

#include "engine/functions.h"

// Overlay of the fields em0b_init touches (offsets are those of Entity).
typedef struct Vars_Em0bInit {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ s32 counter78; // cleared on init
} Vars_Em0bInit;

extern u8 em2b_hitbox[]; // em2b_hitbox, shared with em0b

// Starts em0b (original em0b_init(OBJ_WORK_*)), 0x0202c260.
void em0b_init(Entity *e);

#endif
