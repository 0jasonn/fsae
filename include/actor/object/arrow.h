#ifndef ACTOR_OBJECT_ARROW_H
#define ACTOR_OBJECT_ARROW_H

// Arrow module (src/actor/object/arrow*.cpp). Callees that functions.h does not declare yet, with their dsd names.
// The reviewer moves the ones with an original name into functions.h.
#include "engine/functions.h"

void func_020841b0(Entity *e);
void func_02086168(Entity *e);

#include "engine/player.h"

// Arrow-only fields that Entity does not name (overlay on unk_64).
typedef struct ArrowVars {
    u8 unk_00[0x64];
    s32 hitOffsetX; // 0x64: low half is the x offset of the wall-hit probe
    s32 hitOffsetY; // 0x68: low half is the y offset of the wall-hit probe
    u8 lifetime;    // 0x6c: frames left; the arrow blinks for the last 0x18
} ArrowVars;

extern const u8 arrow_hitboxUpDown[8];   // 0x020cd680: hitbox of an arrow flying up or down
extern const s8 arrow_spawnOffsets[8];   // 0x020cd688: x offset from the owner at [animationState], y offset at [+1]
extern const u8 arrow_hitboxSideways[8]; // 0x020cd690: hitbox of an arrow flying left or right

void arrow_init(Entity *e); // arrow_init(OBJ_WORK_ *), 0x02021004

#endif
