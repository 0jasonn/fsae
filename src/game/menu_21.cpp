#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"
#include "game/menu_wip.h"

// Functions in this file (provisional names, role not confirmed):
//   Menu_Init (Menu_Init)

// Menu_Init (0x020be0c4): stores the result of func_020be128 in the menu and runs the setup calls; begins the menu
// when func_020bac20 reports -1, otherwise runs Menu_SetCursorPos.
extern "C" void Menu_Init(MenuWork *menu);
ARM void Menu_Init(MenuWork *menu) {
    MenuWork *ref;
    s32 value;

    ref = menu;
    value = func_020be128(&ref);
    *(s32 *)((u8 *)menu + 0x348) = value;
    func_020b8c78(value, data_02127178, (u8 *)menu + 0x40500, &ref);
    func_020ba948(menu->unk_358, *(s32 *)((u8 *)menu + 0x348));
    if (func_020bac20(menu->unk_358) != -1) {
        Menu_SetCursorPos(menu);
    } else {
        Menu_Begin(menu);
    }
}

