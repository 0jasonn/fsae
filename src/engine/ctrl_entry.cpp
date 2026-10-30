#include "engine/functions.h"
#include "global.h"
#include "types.h"

// ctrl_entry: function Ctrl_getItemEntry (0x020b9fac), provisional name.

extern u8 data_02126efc[];

// Item of a list of children (0x18 bytes, the same record as RectSlotItem in src/engine/rect_slot.cpp)
typedef struct CtrlItem {
    void *unk_00;      // 0x00
    void *first;       // 0x04: first child, which starts with a u16 status
    void *unk_08;      // 0x08
    void **unk_0c;     // 0x0c
    void **children;   // 0x10
    u16 count;         // 0x14
} CtrlItem;

// Holder at the controller's +0x14: the item array and its length
typedef struct CtrlItemList {
    CtrlItem *items;   // 0x00
    u16 count;         // 0x04
} CtrlItemList;

// Entry of a window: the child object and a flag byte (8 bytes)
typedef struct CtrlEntry {
    void *obj;         // 0x00: the child, or data_02126efc when the child has status 0
    u8 flag;           // 0x04: 1 when the item has children
} CtrlEntry;

// Ctrl_getItemEntry(list, index) (0x020b9fac, provisional name): returns the first child of item index of list, or
// data_02126efc when that child has status 0, and whether the item has any children (count != 0)
extern "C" CtrlEntry Ctrl_getItemEntry(CtrlItemList *list, s16 index);
ARM CtrlEntry Ctrl_getItemEntry(CtrlItemList *list, s16 index) {
    CtrlItem *item = list->items + index;
    CtrlEntry entry;

    entry.obj = item->first;
    if (*(u16 *)entry.obj == 0) {
        entry.obj = data_02126efc;
    }
    entry.flag = (item->count != 0) ? 1 : 0;
    return entry;
}
