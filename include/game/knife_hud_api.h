#ifndef GAME_KNIFE_HUD_API_H
#define GAME_KNIFE_HUD_API_H

// Functions defined in src/game/knife_hud*.cpp.

#include "engine/entity.h"

extern "C" {
void Knife_Hud_HudManager_StatusUpMarker_emptyDtor(void *self);
void Knife_Interp_VecFx32_emptyDtor(void *self);
}

#endif
