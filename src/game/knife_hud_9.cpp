#include "engine/functions.h"
#include "global.h"
#include "game/knife_hud.h"
#include "game/knife_hud_layout.h"

// Functions in this file (original names from the debug build):
//   HudManager::update (0x0209e26c)

namespace Knife {
namespace Hud {

// HudManager::update(int) (0x0209e26c): clears the 24 OAM entries of mode, then updates the HUD for the state
ARM void HudManager::update(int mode) {
    KnifeHudVars *v = (KnifeHudVars *)this;
    s32 i;
    u8 *base;

    if (initialized == 0) {
        return;
    }
    base = objAffineSet + (mode << 10);
    for (i = 0; i < 24; i++) {
        *(u32 *)(base + i * 8) = 0x10002f0;
        *(u16 *)(base + i * 8 + 4) = 0;
    }
    if (v->state170 == 0) {
        if (data_0212c618[0] == 0) {
            return;
        }
        Knife_Hud_HudManager_updateEquipIcon(this, mode);
        Knife_Hud_HudManager_updateStatusUp(this, mode);
        Knife_Hud_HudManager_updateCall(this, mode);
    } else {
        if ((u32)(v->state170 - 2) > 1) {
            return;
        }
        Knife_Hud_HudManager_updateGameOver(this, mode);
    }
}

}
}
