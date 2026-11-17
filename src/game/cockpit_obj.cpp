#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpit_9.h"

// Control words of the two HUD tile objects at data_0212c4a0 (see CockpitInit in cockpit_11.cpp): bits 8-9 of the
// 32-bit word at 0x08 and of the one at 0x10 hold the same two-bit setting.
typedef struct HudTileObjSelect {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08a : 8;
    u32 firstSetting : 2;
    u32 unk_08b : 22;
    u32 unk_0c;
    u32 unk_10a : 8;
    u32 secondSetting : 2;
    u32 unk_10b : 22;
} HudTileObjSelect;

extern HudTileObjSelect data_0212c4a0;

void cockpit_obj_set(u8 index) {
    data_0212c4a0.secondSetting = index;
    data_0212c4a0.firstSetting = data_0212c4a0.secondSetting;
}
