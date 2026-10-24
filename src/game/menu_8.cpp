#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

// Clears the three slot values and the extra value at 0x61c.
ARM void Menu_ClearSlots(MenuWork *menu) {
    s32 i;

    for (i = 0; i < 3; i++) {
        menu->sub.unk_616[i] = 0;
    }
    menu->sub.unk_61c = 0;
}

// Sets the blend brightness of the main screen (0x04000050) and the sub screen (0x04001050). The main screen is
// skipped when the object at 0x358 has its flag byte set.
ARM void Menu_SetBrightness(MenuWork *menu, s32 value) {
    if (menu->unk_358->flagAd == 0) {
        G2x_SetBlendBrightness_(0x4000050, 0x28, value);
    }
    G2x_SetBlendBrightness_(0x4001050, 0x28, value);
}

// Sets the alpha blend of the two screens from a signed level: a positive level sets the fade, zero or negative
// levels set the target. The main screen registers are written only when the flag byte of the object at 0x358 is
// clear.
ARM void Menu_SetBlendLevel(MenuWork *menu, s32 level) {
    s32 target;
    s32 fade;
    s32 value;
    u8 flag;

    target = 0;
    flag = menu->unk_358->flagAd;
    fade = 0x100;
    if (level > 0) {
        fade = 0x100 - level;
    } else {
        target = -level;
    }
    if (flag == 0) {
        value = ((target << 8) & 0xff00) | (fade & 0xff);
        *(u16 *)0x4000040 = value;
        *(u16 *)0x4000044 = 0x94;
    }
    value = ((target << 8) & 0xff00) | (fade & 0xff);
    *(u16 *)0x4001040 = value;
    *(u16 *)0x4001044 = 0x12c0;
}

// Moves the view: the position is derived from the value (0xae or 0x142 when the flag is clear).
ARM void Menu_UpdateView(MenuWork *menu, s32 flag) {
    MenuView *view;
    s16 pos[2];
    s32 value;

    view = menu->unk_364;
    value = flag ? 0xae : 0x142;
    pos[0] = view->posX;
    pos[1] = value / 2 + 0x12;
    view->SetPos(pos);
    func_020b88dc(menu->unk_364, value);
}

// Reads the rectangle (x, y, width, height) of the screen area into rect.
ARM void Menu_GetRect(s16 *rect, s32 unused) {
    s16 tmp[4];

    lobby_copyBounds(tmp);
    rect[0] = tmp[0];
    rect[1] = tmp[1];
    rect[2] = tmp[2];
    rect[3] = tmp[3];
}

// Clears the list state.
ARM void Menu_ClearList(MenuList *list) {
    list->unk_00 = 0;
    list->active = 0;
    list->unk_08 = 0;
    list->unk_0c = 0;
    list->unk_0e = 0;
    list->unk_10 = 0;
    list->unk_14 = 0;
    list->unk_16 = 0;
    list->unk_18 = 0;
    list->unk_1c = 0;
    list->unk_1e = 0;
    list->unk_20 = 0;
    list->unk_22 = 0;
    list->unk_24 = 0;
    list->unk_26 = 0;
    list->unk_28 = 0;
}

// Empty hook (no work).
ARM void Menu_NoOp(void) {
}

// Stores one word.
ARM void Menu_SetWord(s32 *dst, s32 value) {
    *dst = value;
}

// Sets the active flag and, when it is set, resets the scroll state of the list.
ARM void Menu_SetActive(MenuList *list, s32 value) {
    list->active = value;
    if (value != 0) {
        Menu_ResetScroll(list);
        Menu_SyncListRect(list);
    }
}

// Resets the scroll position of the list.
ARM void Menu_ResetScroll(MenuList *list) {
    list->unk_20 = 0;
    Menu_SyncScroll(list);
    list->unk_1c = list->unk_20;
    list->unk_1e = list->unk_20 + list->unk_0e;
    list->unk_24 = list->unk_20;
}

