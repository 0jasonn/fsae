#include "engine/functions.h"
#include "global.h"
#include "ui/widget/menu.h"
#include "ui/widget/menu_wip.h"

// Functions in this file (provisional names, role not confirmed):
//   Menu_DispatchKeys (Menu_DispatchKeys)

// Menu_DispatchKeys (0x020bd968): dispatches the key bits of the input word at sub+0x3a0 (0x20, 0x10, 0x04, 0x01,
// 0x08) to the menu actions. Returns 1 when an action ran, 0 when nothing was done.
extern "C" s32 Menu_DispatchKeys(MenuWork *menu);
s32 Menu_DispatchKeys(MenuWork *menu) {
    u8 step;
    s32 result;
    u16 keys;

    if (Ctrl_isReady(menu->unk_358) != 0) {
        return 0;
    }
    result = 0;
    keys = *(u16 *)((u8 *)menu + 0x403a0);
    if (keys & 0x20) {
        if (func_020bb450(menu->unk_358) != 0) {
            Menu_SetCursorPos(menu);
            result = 1;
        }
    } else if (keys & 0x10) {
        if (func_020bb56c(menu->unk_358) != 0) {
            Menu_SetCursorPos(menu);
            result = 1;
        }
    } else if (keys & 0x4) {
        result = Ctrl_tryChange(menu->unk_358, &step);
        if (result != 0) {
            Menu_Step(menu, step);
        }
    } else if (keys & 0x1) {
        Menu_UpdateView(menu, Ctrl_updateAd(menu->unk_358));
        result = 1;
    } else if (keys & 0x8) {
        Menu_Finish(menu);
        result = 1;
    }
    return result;
}

// Steps the menu: a nonzero flag starts the menu sequence, otherwise the object at 0x358 is asked and an error
// result (-1) is returned as is. (The original returns the register left by Menu_Begin, so this is void.)
void Menu_Step(MenuWork *menu, s32 flag) {
    s32 result;

    if (flag != 0) {
        Menu_Begin(menu);
        return;
    }
    result = Ctrl_getSliderIndexA(menu->unk_358);
    if (result == -1) {
        return;
    }
    Menu_SetCursorPos(menu);
}

// Marks the menu as finished (the flag at sub+0x621) and tells the object at 0x358.
void Menu_Finish(MenuWork *menu) {
    Ctrl_setCounterA(menu->unk_358);
    menu->sub.unk_621 = 1;
}

// Copies the three table pointers into the menu and points the sub-object at them.
void Menu_SetTable(MenuWork *menu, void *const *table) {
    s32 i;

    for (i = 0; i < 3; i++) {
        menu->unk_0f0[i] = table[i];
    }
    menu->sub.unk_378 = menu->unk_0f0;
}

// Clears the video memory (BG and OBJ VRAM, palettes) before the menu starts.
void Menu_ClearVram(void) {
    Vram_SetLcdcBits(0x1ff);
    MIi_CpuClearFast(0, (void *)0x6800000, 0xa4000);
    Vram_DisableBankTail();
    MIi_CpuClearFast(0xc0, (void *)0x7000000, 0x400);
    MIi_CpuClearFast(0, (void *)0x5000000, 0x400);
    MIi_CpuClearFast(0xc0, (void *)0x7000400, 0x400);
    MIi_CpuClearFast(0, (void *)0x5000400, 0x400);
}
