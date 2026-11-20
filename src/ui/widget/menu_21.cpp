#include "engine/functions.h"
#include "global.h"
#include "ui/widget/menu.h"

// TODO(headers): this declaration of RectSpan_create differs from the shared one (ui/widget/uiobj_create.h returns
// void *); see the header restructure report.
extern "C" s32 RectSpan_create(void *ref);
extern u8 data_02127178[];
// TODO(headers): this declaration of RectSpan_callAndMore differs from the shared one;
// see the header restructure report.
extern "C" void RectSpan_callAndMore(s32 value, void *data, void *obj, void *ref);
// TODO(headers): this declaration of Ctrl_setItemList differs from the shared one; see the header restructure report.
extern "C" void Ctrl_setItemList(void *obj, s32 value);

// Functions in this file (provisional names, role not confirmed):
//   Menu_Init (Menu_Init)

// Menu_Init (0x020be0c4): stores the result of RectSpan_create in the menu and runs the setup calls; begins the menu
// when Ctrl_getSliderIndexA reports -1, otherwise runs Menu_SetCursorPos.
extern "C" void Menu_Init(MenuWork *menu);
void Menu_Init(MenuWork *menu) {
    MenuWork *ref;
    s32 value;

    ref = menu;
    value = RectSpan_create(&ref);
    *(s32 *)((u8 *)menu + 0x348) = value;
    RectSpan_callAndMore(value, data_02127178, (u8 *)menu + 0x40500, &ref);
    Ctrl_setItemList(menu->unk_358, *(s32 *)((u8 *)menu + 0x348));
    if (Ctrl_getSliderIndexA(menu->unk_358) != -1) {
        Menu_SetCursorPos(menu);
    } else {
        Menu_Begin(menu);
    }
}

