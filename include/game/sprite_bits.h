#ifndef GAME_SPRITE_BITS_H
#define GAME_SPRITE_BITS_H

#include "engine/entity.h"

// Bits 2 and 3 of the sprite settings word as separate flags (Entity.spriteSettings declares them as one 2-bit field
// b2). Proposed shared change: split b2 into two 1-bit fields.
typedef struct SpriteFlagBitsView {
    u32 low : 2;
    u32 flag2 : 1;
    u32 flag3 : 1;
    u32 high : 28;
} SpriteFlagBitsView;
#define SPRITE_FLAGS(e) ((SpriteFlagBitsView *)&(e)->spriteSettings)

#endif
