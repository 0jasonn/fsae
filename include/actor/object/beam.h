#ifndef ACTOR_OBJECT_BEAM_H
#define ACTOR_OBJECT_BEAM_H

// Beam (module beam): the sword beam shot by a player at full health. Original names from the debug build: beam_init,
// beam_move.
#include "engine/functions.h"
#include "engine/player.h"

// Beam-only fields that Entity does not name (overlay on unk_64).
typedef struct BeamVars {
    u8 unk_00[0x64];
    s32 lifetime; // 0x64: counts down each frame; the beam is removed at 0
} BeamVars;

extern const u8 beam_hitbox[8]; // 0x020f24cc

void beam_init(Entity *e); // beam_init(OBJ_WORK_ *), 0x02021784
void beam_move(Entity *e); // beam_move(OBJ_WORK_ *), 0x020218a0

#endif
