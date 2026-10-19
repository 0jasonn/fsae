#ifndef WIP_E_BOMB_H
#define WIP_E_BOMB_H

// Bomb module (src/game/bomb*.cpp). Callees and fields that functions.h does not declare yet.
#include "engine/functions.h"
#include "object/template.h"

void func_02085ccc(Entity *e); // 0x02085ccc, tail-called by bomb_move

// Bomb-only fields of the Entity overlay (from 0x68 on).
typedef struct BombVars {
    u8 unk_00[0x68];
    s32 carrierLink; // 0x68: non-zero while the bomb is carried; cleared by bomb_lift
} BombVars;

// Table of per-subaction handlers used by bomb_lift (bomb_liftTable).
extern const EntityFunc bomb_liftTable[];
// Hitbox of the bomb (bomb_hitbox).
extern const u8 bomb_hitbox[];

#endif
