#ifndef ACTOR_OBJECT_SET_ITEM_ADD_H
#define ACTOR_OBJECT_SET_ITEM_ADD_H

#include "engine/entity.h"
#include "engine/player.h"

void AddRupeeKakera(Entity *e); // 0x0202639c
void AddKey(Entity *e);         // 0x020262b4
void SetItemAdd(Entity *item, Entity *player); // 0x0205784c

extern "C" {
void Knife_Hud_HudManager_startPowerUpAnim(void *hud, s32 player);   // 0x0209e794
void Knife_Hud_HudManager_startDefenceUpAnim(void *hud, s32 player); // 0x0209e8cc
void Knife_Hud_HudManager_startSpeedUpAnim(void *hud, s32 player);   // 0x0209ea04
}

#endif
