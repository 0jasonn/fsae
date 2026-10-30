#include "engine/functions.h"
#include "global.h"
#include "types.h"

// ctrl_setlist: function Ctrl_setItemList (0x020ba948), provisional name.

extern "C" void Slider_setupItems(void *slider, s32 count);
extern "C" void func_020bafb4(void *self);
extern "C" void Ctrl_setSliderIndexA(void *self, s32 value);
extern "C" void func_020bb898(void *self, s32 flag);
extern "C" void func_020bb148(void *self);
extern "C" void func_020bb208(void *self);

// Item list at +0x14 (item array and count, see ctrl_entry.cpp)
typedef struct CtrlSetItems {
    void *items;       // 0x00
    u16 count;         // 0x04
} CtrlSetItems;

// Controller record for Ctrl_setItemList: the item list at +0x14 and slider A at +0x5c
typedef struct CtrlSetList {
    u8 unk_00[0x14];
    CtrlSetItems *itemList;  // 0x14
    u8 unk_18[0x44];
    void *sliderA;     // 0x5c
} CtrlSetList;

// Ctrl_setItemList(self, list) (0x020ba948, provisional name): stores list at +0x14, sets up slider A for its count, then
// resets slider A to index 0 and calls func_020bb898 when the list is not empty, otherwise calls func_020bb148; finally
// calls func_020bb208
extern "C" void Ctrl_setItemList(void *selfv, CtrlSetItems *list);
ARM void Ctrl_setItemList(void *selfv, CtrlSetItems *list) {
    CtrlSetList *self = (CtrlSetList *)selfv;

    self->itemList = list;
    Slider_setupItems(self->sliderA, list->count);
    func_020bafb4(self);
    if (self->itemList->count != 0) {
        Ctrl_setSliderIndexA(self, 0);
        func_020bb898(self, 1);
    } else {
        func_020bb148(self);
    }
    func_020bb208(self);
}
