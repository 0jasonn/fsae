#include "engine/functions.h"
#include "global.h"
#include "game/knife_hud.h"

// Functions in this file (original names from the debug build):
//   HudManager::getGameOverCharDataType (0x0209ed74)

namespace Knife {
namespace Hud {

// HudManager::getGameOverCharDataType(Knife::Message::Language) const (0x0209ed74): true for languages 5 to 7
ARM BOOL HudManager::getGameOverCharDataType(Knife::Message::Language language) const {
    switch (language) {
    case 5:
    case 6:
    case 7:
        return TRUE;
    default:
        return FALSE;
    }
}

}
}
