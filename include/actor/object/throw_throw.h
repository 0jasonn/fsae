#ifndef ACTOR_OBJECT_THROW_THROW_H
#define ACTOR_OBJECT_THROW_THROW_H

#include "engine/functions.h"
#include "engine/player.h"
#include "actor/object/tama11.h"
#include "knife/comm/singleplay_2.h"

// Player entity fields read by the throw (actor-specific part of the player object)
typedef struct Vars_ThrowOwner {
    /* 00 */ u8 unk_00[0x71];
    /* 71 */ u8 liftState; // nonzero while the player still holds a lifted object (guess)
} Vars_ThrowOwner;

extern const s8 data_020dd038[]; // (dx, dy) of the cell in front, per direction / 4


#endif
