#include "ui/widget/menu_scroll_delta.h"

// Provisional scroll-state fields follow MenuList; each requested step is clamped to 64 pixels.
extern "C" s32 func_020be5a4(MenuList *list, s32 delta) {
    s32 changed = 0;

    if (list->active != 0 && list->unk_20 < list->unk_22) {
        s32 count = Menu_CountItems(list);
        if (count > list->unk_0e) {
            if (delta < 0) {
                s32 step = delta < -0x40 ? -0x40 : delta;
                s32 start = list->unk_20 + step;
                if (start <= 0)
                    start = 0;
                list->unk_1c = start;
                if (list->unk_1c != list->unk_20) {
                    list->unk_1e = list->unk_1c + list->unk_0e;
                    changed = 1;
                }
            }

            if (delta > 0) {
                s32 step = delta > 0x40 ? 0x40 : delta;
                s32 end = list->unk_22 + step;
                if (count <= end)
                    end = count;
                list->unk_1e = end;
                if (list->unk_1e != list->unk_22) {
                    list->unk_1c = list->unk_1e - list->unk_0e;
                    changed = 1;
                }
            }
        }
    }

    return changed;
}
