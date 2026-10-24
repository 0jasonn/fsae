#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "game/knife_hud.h"
#include "game/knife_hud_layout.h"

// Functions in this file (original name from the debug build):
//   HudManager::transferUnactiveEquipIconBasePalette (0x0209ed8c)

s8 subtask_getFlag(u32 index); // C++ symbol _Z15subtask_getFlagm

// HudManager::transferUnactiveEquipIconBasePalette(int) (0x0209ed8c): sends the palette of the unactive equip icon
// for the player's subtask flag, the language selects the row (0x78, 0x7c or 0x80 added to the flag)
extern "C" void Knife_Hud_HudManager_transferUnactiveEquipIconBasePalette(Knife::Hud::HudManager *self, int player);
ARM void Knife_Hud_HudManager_transferUnactiveEquipIconBasePalette(Knife::Hud::HudManager *self, int player) {
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
