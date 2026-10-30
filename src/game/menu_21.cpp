#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"
#include "game/menu_wip.h"

// Functions in this file (provisional names, role not confirmed):
//   Menu_Init (Menu_Init)

// Menu_Init (0x020be0c4): stores the result of func_020be128 in the menu and runs the setup calls; begins the menu
// when Ctrl_getSliderIndexA reports -1, otherwise runs Menu_SetCursorPos.
extern "C" void Menu_Init(MenuWork *menu);
ARM void Menu_Init(MenuWork *menu) {
    MenuWork *ref;
    s32 value;

    ref = menu;
    value = func_020be128(&ref);
    *(s32 *)((u8 *)menu + 0x348) = value;
    RectSpan_callAndMore(value, data_02127178, (u8 *)menu + 0x40500, &ref);
    Ctrl_setItemList(menu->unk_358, *(s32 *)((u8 *)menu + 0x348));
    if (Ctrl_getSliderIndexA(menu->unk_358) != -1) {
        Menu_SetCursorPos(menu);
    } else {
        Menu_Begin(menu);
    }
}

