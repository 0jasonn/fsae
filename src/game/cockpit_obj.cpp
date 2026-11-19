#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpit_9.h"
#include "engine/hud_tile_obj.h"

// Sets the same two-bit setting in both HUD tile objects (data_0212c4a0, see CockpitInit in cockpit_11.cpp).
void cockpit_obj_set(u8 index) {
    data_0212c4a0.entries[1].setting = index;
    data_0212c4a0.entries[0].setting = data_0212c4a0.entries[1].setting;
}
