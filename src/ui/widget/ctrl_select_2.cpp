#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/ctrl_select.h"

// ctrl_select: function Ctrl_advanceSelection (0x020bb56c), provisional name Ctrl_advanceSelection. Moves the selection to the
// next item: first the second slider inside the current item, then the list slider to the next item.

// Ctrl_advanceSelection(self) (0x020bb56c, provisional name): returns 0 when the flag at +0xad is set or nothing could
// move, 5 when the second slider moved, 4 when the list slider moved to the next item (and the item was selected).
// The pool entry 2 or 5 is then acquired, with 10 stored at +0x18 of the object at +0x74 when something moved.
s32 Ctrl_advanceSelection(void *selfv) {
    CtrlSelectObj *self = (CtrlSelectObj *)selfv;
    CtrlRingItem *item;
    s32 result = 0;
    s32 index;

    if (self->flagAd != 0) {
        return result;
    }
    index = self->sliderA->index;
    if (index == -1 || (item = self->itemList->items + index)->count == 0 ||
        self->sliderB->index + 1 >= item->count) {
        if ((s32)self->itemList->count > (s16)(index + 1)) {
            Ctrl_setSliderIndexA(self, (s16)(index + 1));
            Ctrl_selectCurrentItem(self, 0);
            result = 4;
        }
    } else {
        Ctrl_setSliderIndexB(self, (s16)(self->sliderB->index + 1));
        result = 5;
    }
    if (result != 0) {
        RectFlagPair_setFlag(self, 0);
        func_020bb208(self);
        *(u16 *)(self->unk_74 + 0x18) = 10;
        Menu_AcquirePoolEntry(self->pool, 2, 0x80);
    } else {
        Menu_AcquirePoolEntry(self->pool, 5, 0x80);
    }
    return result;
}
