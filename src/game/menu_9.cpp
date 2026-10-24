#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

// Copies the scroll position (0x20) to the second scroll value (0x22).
ARM void Menu_SyncScroll(MenuList *list) {
    list->unk_22 = list->unk_20;
}

// Number of list items: the height of the screen area (from the rectangle) is at least 0xae, plus the list length.
// The second argument is not used (the caller passes its own argument register through).
ARM s32 Menu_CountItems(MenuList *list, s32 value) {
    s16 rect[4];
    s32 span;
    s32 count;

    count = 0;
    if (list->active != 0) {
        func_020b52f8(rect);
        span = (s16)(rect[3] - rect[1]);
        if (span < 0xae) {
            span = 0xae;
        }
        count = (s16)(list->unk_0e + span - 0xae);
    }
    return count;
}

// Nonzero when the item count is larger than the list length (unk_0e).
ARM s32 Menu_IsOverflow(MenuList *list, s32 value) {
    return Menu_CountItems(list, value) > list->unk_0e;
}

// Stores the value at 0x18.
ARM void Menu_SetWord18(MenuList *list, s32 value) {
    list->unk_18 = value;
}
