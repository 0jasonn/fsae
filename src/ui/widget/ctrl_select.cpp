#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/ctrl_select.h"

// ctrl_select: function Ctrl_selectCurrentItem (0x020bb898), provisional name Ctrl_selectCurrentItem.
// Called with flag 1 by Ctrl_setItemList and with flag 0 by the list cursor code (Ctrl_advanceSelection).

// Calls virtual slot `slot` (4 bytes each) of obj
#define CTRL_VSLOT(obj, slot) (((void **)*(void **)(obj))[slot])

// Ctrl_selectCurrentItem(self, flag) (0x020bb898, provisional name): when the current index is inside the visible window
// and its item has children, moves the cursor view to that row and selects it. The mode is 1 when flag is 0 and 0 when
// it is not; with nothing selected it is 2. Then the cursor and the second slider get the selected flag and the mode is
// passed to Ctrl_setMode (func_020bb788).
void Ctrl_selectCurrentItem(void *selfv, s32 flag) {
    CtrlSelectObj *self = (CtrlSelectObj *)selfv;
    CtrlSliderWin *slider;
    CtrlRingItem *item;
    s16 pos[2];
    s32 rel;
    u16 mode;
    s32 sel;
    s32 index;

    slider = self->sliderA;
    index = slider->index;
    sel = 0;
    mode = 2;
    self->selected = sel;
    if (index >= 0) {
        rel = index - slider->windowFirst;
        if (rel >= 0 && rel < slider->windowCount) {
            item = (CtrlRingItem *)((u8 *)self->itemList->items + index * 0x18);
            if (item->count != 0) {
                pos[0] = ((s16 *)self->cursor)[2];
                pos[1] = (s16)((rel + 1) * 0x17);
                ((void (*)(void *, s16 *))CTRL_VSLOT(self->cursor, 2))(self->cursor, pos);
                RectObjLink_callA(self->cursor, self->unk_18, sel);
                self->selected = 1;
                if (flag == 0) {
                    sel = 1;
                }
                mode = (u16)sel;
            }
        }
    }
    ((void (*)(void *, s32))CTRL_VSLOT(self->cursor, 4))(self->cursor, self->selected);
    ((void (*)(void *, s32))CTRL_VSLOT(self->sliderB, 4))(self->sliderB, self->selected);
    func_020bb788(self, mode);
}
