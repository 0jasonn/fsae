#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"
#include "game/menu_wip.h"

// Functions in this file (provisional names, role not confirmed):
//   Menu_DispatchKeys (Menu_DispatchKeys)

// Menu_DispatchKeys (0x020bd968): dispatches the key bits of the input word at sub+0x3a0 (0x20, 0x10, 0x04, 0x01,
// 0x08) to the menu actions. Returns 1 when an action ran, 0 when nothing was done.
extern "C" s32 Menu_DispatchKeys(MenuWork *menu);
ARM s32 Menu_DispatchKeys(MenuWork *menu) {
    u8 step;
    s32 result;
    u16 keys;

    if (func_020bb730(menu->unk_358) != 0) {
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
        result = func_020bb698(menu->unk_358, &step);
        if (result != 0) {
            Menu_Step(menu, step);
        }
    } else if (keys & 0x1) {
        Menu_UpdateView(menu, func_020bb6c8(menu->unk_358));
        result = 1;
    } else if (keys & 0x8) {
        Menu_Finish(menu);
        result = 1;
    }
    return result;
}
