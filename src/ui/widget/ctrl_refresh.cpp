#include "engine/functions.h"
#include "global.h"
#include "ui/widget/ctrl_items.h"

extern u8 data_02126efc[];

// Ctrl_refreshItemRing (0x020bafb4): builds the visible entries of the item list (from the slider's first index,
// at most visible + 1 of them, each with its first child or data_02126efc and a flag) and refreshes slider A with them.
void Ctrl_refreshItemRing(void *self) {
    CtrlRingEntry entries[7];
    s32 i;
    s32 n;
    s32 first;
    void *slider;
    CtrlRingItem *item;

    n = 0;
    first = 0;
    if ((*(CtrlRingItemList **)((u8 *)self + 0x14))->count != 0) {
        slider = *(void **)((u8 *)self + 0x5c);
        first = *(s16 *)((u8 *)slider + 0x22);
        u16 vis = *(u16 *)((u8 *)slider + 0x24);
        u16 limit = (u16)(vis + 1);
        u16 remain = (u16)((*(CtrlRingItemList **)((u8 *)self + 0x14))->count - first);
        n = limit;
        if (remain <= limit) {
            n = remain;
        }
    }
    for (i = 0; i < n; i++) {
        item = &(*(CtrlRingItemList **)((u8 *)self + 0x14))->items[first + i];
        entries[i].obj = item->first;
        if (*(u16 *)entries[i].obj == 0) {
            entries[i].obj = data_02126efc;
        }
        entries[i].flag = (item->count != 0) ? 1 : 0;
    }
    ItemRing_refresh(*(void **)((u8 *)self + 0x5c), entries);
}
