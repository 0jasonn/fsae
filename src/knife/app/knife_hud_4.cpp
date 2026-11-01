#include "engine/functions.h"
#include "global.h"
#include "knife/app/knife_hud.h"
#include "engine/player.h"
#include "knife/app/knife_hud_layout.h"

// Functions in this file (names guessed from the stored state, the debug build has none, except isGameoverMode):
//   HudManager::setStateThree (0x0209ecbc), setStateNone (0x0209ecc8), isGameoverMode (0x0209ecd4)

namespace Knife {
namespace Hud {

// HudManager::setStateThree (0x0209ecbc, name guessed): sets the game-over state to 3
void HudManager::setStateThree(void) {
    state170 = 3;
}

// HudManager::setStateNone (0x0209ecc8, name guessed): clears the game-over state
void HudManager::setStateNone(void) {
    state170 = 0;
}

// HudManager::isGameoverMode() const (0x0209ecd4): true while the game-over state is set
BOOL HudManager::isGameoverMode(void) const {
    return state170 != 0;
}

}
}

// Functions in this file (original names from the debug build):
//   HudManager::getPlayerPos(int, VecFx32 *) const (0x0209ece8)

// The start*Anim functions (0x0209e794, 0x0209e8cc, 0x0209ea04) are parked in scratch/agentE/nonmatching.

extern s16 *data_02158fa0; // scroll position: x at [1], y at [2]
s8 subtask_getFlag(u32 index); // C++ symbol _Z15subtask_getFlagm

// HudManager::getPlayerPos(int, VecFx32 *) const (0x0209ece8): position of the player's entity in pixels of the
// scroll, 20.12 fixed point
extern "C" void Knife_Hud_HudManager_getPlayerPos(const Knife::Hud::HudManager *self, int player, VecFx32 *pos);
void Knife_Hud_HudManager_getPlayerPos(const Knife::Hud::HudManager *self, int player, VecFx32 *pos) {
    PlayerData *pl = &data_0212ceb0[player];
    s16 scrollX = data_02158fa0[1];
    s16 scrollY = data_02158fa0[2];

    pos->x = (pl->entity->x.HALF.HI - scrollX) << 12;
    pos->y = (pl->entity->y.HALF.HI + pl->entity->z.HALF.HI - scrollY) << 12;
    pos->z = 0;
}

// Functions in this file (original names from the debug build):
//   HudManager::getPlayerDir (0x0209ed4c)

extern PlayerData data_0212ceb0[4];

namespace Knife {
namespace Hud {

// HudManager::getPlayerDir(int) const (0x0209ed4c): half the animation value of the player's entity
int HudManager::getPlayerDir(int player) const {
    PlayerData *pl = &data_0212ceb0[player];

    return pl->entity->animationState >> 1;
}

}
}

// Functions in this file (invented name):
//   Knife_Hud_HudManager_getIconSlot (0x0209ed6c)

// Knife_Hud_HudManager_getIconSlot (name invented): index of the player's icon slot, 7 + player
extern "C" s32 Knife_Hud_HudManager_getIconSlot(const Knife::Hud::HudManager *self, int player);
s32 Knife_Hud_HudManager_getIconSlot(const Knife::Hud::HudManager *self, int player) {
    return player + 7;
}

// Functions in this file (original names from the debug build):
//   HudManager::getGameOverCharDataType (0x0209ed74)

namespace Knife {
namespace Hud {

// HudManager::getGameOverCharDataType(Knife::Message::Language) const (0x0209ed74): true for languages 5 to 7
BOOL HudManager::getGameOverCharDataType(Knife::Message::Language language) const {
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

// Functions in this file (original name from the debug build):
//   HudManager::transferUnactiveEquipIconBasePalette (0x0209ed8c)

// HudManager::transferUnactiveEquipIconBasePalette(int) (0x0209ed8c): sends the palette of the unactive equip icon
// for the player's subtask flag, the language selects the row (0x78, 0x7c or 0x80 added to the flag)
extern "C" void Knife_Hud_HudManager_transferUnactiveEquipIconBasePalette(Knife::Hud::HudManager *self, int player);
void Knife_Hud_HudManager_transferUnactiveEquipIconBasePalette(Knife::Hud::HudManager *self, int player) {
    int flag;
    int row;
    void *app;
    u8 language;

    flag = subtask_getFlag(player);
    language = ((u8 *)&data_0212c7c8)[0x8e];
    row = 0x78;
    if (language == 1 || language == 4) {
        row = 0x7c;
    } else if (language == 2) {
        row = 0x80;
    }
    app = KnifeApp_getInstance();
    CgPalletSet((u16 *)KnifeApp_getZeldaResource_08ddcc(app, row + flag), 0x14, 1);
}
