#ifndef WIP_F_CTRL_ITEMS_H
#define WIP_F_CTRL_ITEMS_H

// Item list records used by the controller list code (same layouts as src/engine/ctrl_entry.cpp).

#include "engine/functions.h"

// Item of a list of children (0x18 bytes).
typedef struct CtrlRingItem {
    void *unk_00;
    void *first;      // 0x04: first child, which starts with a u16 status
    void *unk_08;
    void **unk_0c;
    void **children;  // 0x10
    u16 count;        // 0x14
} CtrlRingItem;

// Holder at the controller's +0x14: the item array and its length.
typedef struct CtrlRingItemList {
    CtrlRingItem *items;  // 0x00
    u16 count;            // 0x04
} CtrlRingItemList;

// Entry handed to ItemRing_refresh: the child object and a flag byte (8 bytes).
typedef struct CtrlRingEntry {
    void *obj;
    u8 flag;
} CtrlRingEntry;

extern "C" {
void ItemRing_refresh(void *slider, CtrlRingEntry *entries);
void Ctrl_refreshItemRing(void *self);
}

#endif
