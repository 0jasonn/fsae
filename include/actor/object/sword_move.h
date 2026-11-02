#ifndef WIP_C_SWORD_MOVE_H
#define WIP_C_SWORD_MOVE_H

#include "engine/entity.h"

// Sword actor helpers called by sword_move
extern const s8 swordSpawnOffsets[]; // 0x020dc73c, (dx, dy) pair per sword animation frame (Entity::unk_21)

extern "C" {
void sword_plsync(Entity *e, Entity *owner); // 0x0207b560
void swordEvent(Entity *e);            // 0x0207b908
void func_020841b0(Entity *e);         // thumb
}
void PlWeaponFireCheck(Entity *e); // 0x02054c4c
void zFree(void *p);               // 0x0202a568

// Bit layout of PlayerData::unk_3e: the low two bits hold the current sword level
typedef struct SwordLevelView {
    u8 level : 2;
    u8 rest : 6;
} SwordLevelView;

// Flip bit of the sprite settings word (bit 2 on its own)
typedef struct SwordFlipView {
    u32 low : 2;
    u32 flipX : 1;
    u32 high : 29;
} SwordFlipView;

#endif
