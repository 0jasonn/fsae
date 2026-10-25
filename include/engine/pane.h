#ifndef WIP_F_PANE_H
#define WIP_F_PANE_H

// Pane tree of the 2D UI library (classes Pane, Picture, Window and TextBox; RTTI names N4nt...2d4PaneE and so on).
// A pane has a vtable (slot 0 = class info, slot 1 = release children, slot 2 = set offset, slot 3 = visit), a parent
// link, a child array and a position/size rectangle. Picture and Window add an item pointer and a count.

#include "types.h"

// Spec record read by the Pane constructors (the layout data of a pane in the UI tables)
typedef struct PaneRecord {
    u16 id;          // 0x00: index into the table of the context (see PaneTable)
    u8 kind;         // 0x02
    u8 unk_03;       // 0x03
} PaneRecord;

typedef struct PaneSpec {
    u8 unk_00[8];
    s16 x;           // 0x08
    s16 y;           // 0x0a
    s16 w;           // 0x0c
    s16 h;           // 0x0e
    u16 id;          // 0x10: index of the picture in the context table
    u8 count;        // 0x12: number of records
    u8 unk_13;
    PaneRecord records[1]; // 0x14: count records of 4 bytes
} PaneSpec;

// Table of 32-bit entries (the base at +4 of the table)
typedef struct PaneTable {
    u8 unk_00[4];
    u32 *base;       // 0x04
} PaneTable;

// Context passed to the constructors, its table at +0xc
typedef struct PaneCtx {
    u8 unk_00[0xc];
    PaneTable *table; // 0x0c
} PaneCtx;

// Pane object. Picture and Window use the item fields at 0x20 and 0x24.
typedef struct Pane {
    void *vtable;             // 0x00
    struct Pane *parent;      // 0x04: set by Pane_appendChild
    struct Pane **children;   // 0x08
    s16 posX;                 // 0x0c
    s16 posY;                 // 0x0e
    s16 ofsX;                 // 0x10: offset of the children, set by Pane_setOffset
    s16 ofsY;                 // 0x12
    s16 sizeX;                // 0x14
    s16 sizeY;                // 0x16
    u16 childCount;           // 0x18
    u16 childCapacity;        // 0x1a
    u8 flag1c;                // 0x1c
    u8 unk_1d[1];
    u16 id1e;                 // 0x1e: Window only
    void *items;              // 0x20: Picture, a u32 pointer; Window, an array of PaneItem
    u8 itemCount;             // 0x24
} Pane;

// Item of a Window (stride 8)
typedef struct PaneItem {
    u32 *source;              // 0x00: base + id of the table
    u8 kind;                  // 0x04
    u8 unk_05[3];
} PaneItem;

// Virtual slot call: slot n of the vtable of a pane, with two arguments
typedef void (*PaneSlotFn)(void *self, void *arg);
#define PANE_SLOT(self, n) (((PaneSlotFn *)(*(void **)(self)))[n])

// Virtual slot call with three arguments (slot 2 is Pane_setOffset(self, ctx, delta))
typedef void (*PaneSlot3Fn)(void *self, void *ctx, void *delta);
#define PANE_SLOT3(self, n) (((PaneSlot3Fn *)(*(void **)(self)))[n])

extern u8 data_02126a60[];   // class info of Pane (returned by Pane_getClassInfo)
extern u8 data_02126a88[];   // vtable of Pane
extern u8 data_02126a98[];   // class info of Picture (returned by Picture_getClassInfo)
extern u8 data_02126ac4[];   // vtable of Picture
extern u8 data_02126b00[];   // vtable of Window

// Shared functions this file calls, declared here (the original names of the lobby and the allocator)
extern "C" void lobby_releaseObj(void *heap, void *obj);
extern "C" void *func_020c2c34(void *heap, s32 size);
extern "C" void func_020c2c48(void *heap, void *block);
extern "C" void *func_020b6bf8(void *self, void *spec, void *ctx);
extern "C" void Window_allocItems(void *self, void *arg);

#endif
