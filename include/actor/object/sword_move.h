#ifndef ACTOR_OBJECT_SWORD_MOVE_H
#define ACTOR_OBJECT_SWORD_MOVE_H

#include "engine/entity.h"

// Sword actor helpers called by sword_move
extern const s8 swordSpawnOffsets[]; // 0x020dc73c, (dx, dy) pair per sword animation frame (Entity::unk_21)

extern "C" {
void swordEvent(Entity *e);            // 0x0207b908
}

// Flip bit of the sprite settings word (bit 2 on its own)
typedef struct SwordFlipView {
    u32 low : 2;
    u32 flipX : 1;
    u32 high : 29;
} SwordFlipView;

#endif
