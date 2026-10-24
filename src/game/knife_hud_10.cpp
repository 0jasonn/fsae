#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "game/knife_hud.h"
#include "game/knife_hud_layout.h"

// Functions in this file (invented name):
//   Knife_Hud_HudManager_getIconSlot (0x0209ed6c)


// Knife_Hud_HudManager_getIconSlot (name invented): index of the player's icon slot, 7 + player
extern "C" s32 Knife_Hud_HudManager_getIconSlot(const Knife::Hud::HudManager *self, int player);
ARM s32 Knife_Hud_HudManager_getIconSlot(const Knife::Hud::HudManager *self, int player) {
    return player + 7;
}
