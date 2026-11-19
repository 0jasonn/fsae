#ifndef OBJECT_SET2F_H
#define OBJECT_SET2F_H

#include "engine/entity.h"

#include "engine/map_state.h"
typedef struct Vars_Set2f {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u8 triggered; // set once set2f_move has flipped the actor
} Vars_Set2f;

#endif
