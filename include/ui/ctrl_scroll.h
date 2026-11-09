#ifndef UI_CTRL_SCROLL_H
#define UI_CTRL_SCROLL_H

#include "engine/functions.h"

// A pair of s16 passed by pointer to the virtual setPos (slot 2) of the Ctrl sub objects
typedef struct CtrlPos16 {
    s16 x;
    s16 y;
} CtrlPos16;

// Panel object of the Ctrl: starts with a vtable (slot 2 = setPos, slot 4 = setSelected); embedded ones sit at +0x20 and
// +0x3c of the Ctrl. Only declared (never defined) so no vtable is emitted.
class CtrlPanel {
public:
    virtual void slot0() = 0;
    virtual void slot1() = 0;
    virtual void setPos(const CtrlPos16 *pos) = 0;
    virtual void slot3() = 0;
    virtual void setSelected(s32 selected) = 0;

    s16 x;                 // 0x04
    s16 y;                 // 0x06
    u8 unk_08[0x20 - 0x08];
    u16 itemCount;         // 0x20 (list pane): number of items
    u8 unk_22[2];
    u16 rowCount;          // 0x24 (list pane): visible rows minus one
    u8 unk_26[3];
    u8 highlight;          // 0x29 (row): set when the row holds the selected item
    s16 selectedIndex;     // 0x2a (list pane): selected item, -1 for none
    u8 unk_2c[4];
    CtrlPanel **rows;      // 0x30 (list pane): the row panels, indexed by item % (rowCount + 1)
    s16 *rowItem;          // 0x34 (list pane): the item each row currently shows
    s16 rangeCurrent;      // 0x38 (list pane): current scroll offset in pixels
    s16 rangeTarget;       // 0x3a (list pane): target scroll offset
    u8 enabled;            // 0x3c (list pane)
};

// Ctrl object, only the fields touched by Ctrl_updateScroll (0x020bacb8).
typedef struct CtrlScrollObj {
    /* 00 */ u8 unk_00[0x14];
    /* 14 */ void *itemList;
    /* 18 */ u8 unk_18[0x20 - 0x18];
    /* 20 */ u8 panelA[0x3c - 0x20];   // embedded CtrlPanel A at +0x20, B at +0x3c
    /* 3c */ u8 panelB[0x5c - 0x3c];
    /* 5c */ CtrlPanel *listPane;
    /* 60 */ CtrlPanel *sidePane;
    /* 64 */ u8 unk_64[0x68 - 0x64];
    /* 68 */ void *timer68;
    /* 6c */ void *timer6c;
    /* 70 */ void *timer70;
    /* 74 */ void *timer74;
    /* 78 */ u8 unk_78[0x88 - 0x78];
    /* 88 */ CtrlPanel *cursor;
    /* 8c */ u8 unk_8c[0x9a - 0x8c];
    /* 9a */ s16 sideTargetX;
    /* 9c */ u16 mode;
    /* 9e */ s16 offsetTarget;
    /* a0 */ s16 offsetCurrent;
    /* a2 */ u8 unk_a2[0xad - 0xa2];
    /* ad */ u8 opening;
    /* ae */ u8 selected;
} CtrlScrollObj;

// Item entry returned by the getter (Ctrl_getItemEntry, 8 bytes)
typedef struct CtrlItemEntry {
    void *obj;
    u8 flag;
} CtrlItemEntry;

extern "C" {
void Ctrl_updateScroll(CtrlScrollObj *self);
void Ctrl_setStateValue(void *self);
void RectObjList_countDown(void *list);
CtrlItemEntry Ctrl_getItemEntry(void *list, s16 index);
s32 func_020b9df0(CtrlPanel *slider, CtrlItemEntry (*getter)(void *, s16), void *itemList);
void Ctrl_drawListRow(CtrlPanel *slider, const CtrlItemEntry &entry, s32 index);
}

#endif
