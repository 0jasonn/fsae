#ifndef WIP_C_SHIELD_H
#define WIP_C_SHIELD_H

#include "engine/entity.h"

// Shield actor fields past the shared Entity header
typedef struct Vars_Shield {
    /* 00 */ u8 unk_00[0x65];
    /* 65 */ u8 hitSoundTimer; // 8 after a hit sound was requested
} Vars_Shield;

// Flip bits of the sprite settings word (bit 2 and bit 3 on their own)
typedef struct SpriteFlipView {
    u32 low : 2;
    u32 flipX : 1;
    u32 flipY : 1;
    u32 high : 28;
} SpriteFlipView;
#define SPRITE_FLIP(e) ((SpriteFlipView *)&(e)->spriteSettings)

extern const void *const shieldHitboxTable[]; // 0x021166f8, hitbox per half animation state of the owner

extern "C" {
void func_020841b0(Entity *e); // thumb
void func_02084320(Entity *e); // thumb
}

#endif
