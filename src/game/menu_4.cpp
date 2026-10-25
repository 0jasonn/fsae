#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

// Steps the menu: a nonzero flag starts the menu sequence, otherwise the object at 0x358 is asked and an error
// result (-1) is returned as is. (The original returns the register left by Menu_Begin, so this is void.)
ARM void Menu_Step(MenuWork *menu, s32 flag) {
    s32 result;

    if (flag != 0) {
        Menu_Begin(menu);
        return;
    }
    result = func_020bac20(menu->unk_358);
    if (result == -1) {
        return;
    }
    Menu_SetCursorPos(menu);
}

// Marks the menu as finished (the flag at sub+0x621) and tells the object at 0x358.
ARM void Menu_Finish(MenuWork *menu) {
    func_020bb70c(menu->unk_358);
    menu->sub.unk_621 = 1;
}

// Copies the three table pointers into the menu and points the sub-object at them.
ARM void Menu_SetTable(MenuWork *menu, void *const *table) {
    s32 i;

    for (i = 0; i < 3; i++) {
        menu->unk_0f0[i] = table[i];
    }
    menu->sub.unk_378 = menu->unk_0f0;
}

// Clears the video memory (BG and OBJ VRAM, palettes) before the menu starts.
ARM void Menu_ClearVram(void) {
    func_0201500c(0x1ff);
    MIi_CpuClearFast(0, (void *)0x6800000, 0xa4000);
    func_02015448();
    MIi_CpuClearFast(0xc0, (void *)0x7000000, 0x400);
    MIi_CpuClearFast(0, (void *)0x5000000, 0x400);
    MIi_CpuClearFast(0xc0, (void *)0x7000400, 0x400);
    MIi_CpuClearFast(0, (void *)0x5000400, 0x400);
}
