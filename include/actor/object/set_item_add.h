#ifndef WIP_C_SET_ITEM_ADD_H
#define WIP_C_SET_ITEM_ADD_H

#include "engine/entity.h"
#include "engine/player.h"

// Bit layout of PlayerData::unk_3e: the three power-up levels (0..2) collected by the player
typedef struct PowerUpLevels {
    u8 power : 2;
    u8 defence : 2;
    u8 speed : 2;
    u8 rest : 2;
} PowerUpLevels;
#define POWERUP_LEVELS(p) ((PowerUpLevels *)&(p)->unk_3e)


void AddRupeeKakera(Entity *e); // 0x0202639c
void AddKey(Entity *e);         // 0x020262b4
void SetItemAdd(Entity *item, Entity *player); // 0x0205784c

extern "C" {
void DropRupees(u8 type, u16 amount); // 0x02050504
void Knife_Hud_HudManager_startPowerUpAnim(void *hud, s32 player);   // 0x0209e794
void Knife_Hud_HudManager_startDefenceUpAnim(void *hud, s32 player); // 0x0209e8cc
void Knife_Hud_HudManager_startSpeedUpAnim(void *hud, s32 player);   // 0x0209ea04
}

#endif
