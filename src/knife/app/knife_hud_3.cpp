#include "engine/functions.h"
#include "global.h"
#include "knife/app/knife_hud.h"
#include "knife/message/knife_hud_e.h"
#include "knife/subtask/subtask_calls.h"
#include "engine/player.h"
#include "knife/app/knife_hud_layout.h"

// Functions in this file (original names from the debug build, or guessed where marked):
//   HudManager::startCallAnim (0x0209eb3c), isJustStartedCallAnim (0x0209eb58), setStateOne (0x0209eb70, name guessed)

namespace Knife {
namespace Hud {

// HudManager::startCallAnim(int) (0x0209eb3c): a call animation that is pending (negative) starts and is cleared
BOOL HudManager::startCallAnim(int player) {
    if (callAnim[player] < 0) {
        callAnim[player] = 0;
        return TRUE;
    }
    return FALSE;
}

// HudManager::isJustStartedCallAnim(int) const (0x0209eb58): true while the call animation has just started
BOOL HudManager::isJustStartedCallAnim(int player) const {
    return callAnim[player] == 1;
}

// HudManager::setStateOne (0x0209eb70, name guessed): sets the game-over state to 1
void HudManager::setStateOne(void) {
    state170 = 1;
}

}
}

// HudManager::startGameOverAnim() (0x0209eb7c): sets up the record table of the GAMEOVER banner. Each character of the
// banner (per language) is looked up in the glyph table of the char data type (index -1 when missing), gets its x
// position and a start delay spread over 0x78 frames, then the game-over state becomes 2.
void Knife_Hud_HudManager_startGameOverAnim(Knife::Hud::HudManager *self) {
    KnifeHudVars *hud = (KnifeHudVars *)self;
    s32 language = KnifeApp_getCurrentLanguage(KnifeApp_getInstance());
    s32 type = self->getGameOverCharDataType((Knife::Message::Language)language);
    const KnifeHudBannerChars *chars = &data_020ddd8c[language];
    s32 found;
    s32 count = 0;
    s32 i;

    while (chars->ch[count] != 0) {
        found = -1;
        for (i = 0; data_020ddecc[type].entry[i].code != 0; i++) {
            if (chars->ch[count] == data_020ddecc[type].entry[i].code) {
                found = i;
                break;
            }
        }
        hud->records[count].unk_00 = found;
        hud->records[count].unk_04 = data_020de1dc[language].x[count] << 12;
        hud->records[count].unk_08 = -0x50000;
        hud->records[count].unk_0c = 0;
        hud->records[count].unk_10 = 0;
        count++;
    }
    hud->records[count].unk_00 = -1;
    for (i = 0; i < count; i++) {
        hud->records[i].unk_10 = i * 0x78 / count;
    }
    hud->state170 = 2;
}

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
    PlayerData *pl = &playerWork[player];
    s16 scrollX = data_02158fa0[1];
    s16 scrollY = data_02158fa0[2];

    pos->x = (pl->entity->x.HALF.HI - scrollX) << 12;
    pos->y = (pl->entity->y.HALF.HI + pl->entity->z.HALF.HI - scrollY) << 12;
    pos->z = 0;
}

// Functions in this file (original names from the debug build):
//   HudManager::getPlayerDir (0x0209ed4c)

extern PlayerData playerWork[4];

namespace Knife {
namespace Hud {

// HudManager::getPlayerDir(int) const (0x0209ed4c): half the animation value of the player's entity
int HudManager::getPlayerDir(int player) const {
    PlayerData *pl = &playerWork[player];

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
    language = ((u8 *)&gameState)[0x8e];
    row = 0x78;
    if (language == 1 || language == 4) {
        row = 0x7c;
    } else if (language == 2) {
        row = 0x80;
    }
    app = KnifeApp_getInstance();
    CgPalletSet((u16 *)KnifeApp_getZeldaResource_08ddcc(app, row + flag), 0x14, 1);
}
