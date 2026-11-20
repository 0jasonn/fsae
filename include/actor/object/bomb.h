#ifndef ACTOR_OBJECT_BOMB_H
#define ACTOR_OBJECT_BOMB_H

// Bomb module (src/game/bomb*.cpp). Callees and fields that functions.h does not declare yet.
#include "engine/functions.h"
#include "engine/player.h"


// Bomb-only fields of the Entity overlay (from 0x68 on).
typedef struct BombVars {
    u8 unk_00[0x68];
    s32 carrierLink; // 0x68: non-zero while the bomb is carried; cleared by bomb_lift
} BombVars;

// Table of per-subaction handlers used by bomb_lift (bomb_liftTable).
extern const EntityFunc bomb_liftTable[];
// Hitbox of the bomb (bomb_hitbox).
extern const u8 bomb_hitbox[];
void BombWallCk(Entity *e); // original BombWallCk(OBJ_WORK_*)

#endif
