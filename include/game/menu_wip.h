#ifndef WIP_G_MENU_WIP_H
#define WIP_G_MENU_WIP_H

// Declarations for the unnamed menu helpers of implementer G (round 15). Callees that are not in
// engine/functions.h or game/menu.h are declared here; the reviewer moves the shared ones.

#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

// Object embedded in the menu at 0x40500 and 0x403f8: its first word is a vtable pointer. Slot numbers follow the
// order of the virtual functions (slot 4 at +0x10, slot 5 at +0x14).
struct MenuSlotObj {
    virtual void Slot0(void);
    virtual void Slot1(void);
    virtual void Slot2(void);
    virtual void Slot3(void);
    virtual void Slot4(s32 id);
    virtual s32 Slot5(s32 tag, s32 id, void *data);
};

// State copied from a list by Menu_CopyViewState: a rectangle (filled by Menu_GetRect), then fields at +0x10..+0x1c.
typedef struct MenuViewState {
    /* 00 */ s16 rect[4];
    /* 08 */ u8 unk_08[0x10 - 0x08];
    /* 10 */ u32 unk_10;
    /* 14 */ s16 unk_14;
    /* 16 */ s16 unk_16;
    /* 18 */ u32 unk_18;
    /* 1c */ u32 unk_1c;
    /* 20 */ u32 unk_20;
} MenuViewState;

// Key record updated by Menu_ReadKeyEdges: pressed and released edges and the held keys.
typedef struct MenuKeys {
    /* 00 */ u16 pressed;
    /* 02 */ u16 released;
    /* 04 */ u16 held;
} MenuKeys;

// Sound object referenced by a menu sound handle (fields by the offsets used in the sound helpers).
typedef struct MenuSoundObj {
    /* 00 */ u8 unk_00[0x34];
    /* 34 */ u16 state;
    /* 36 */ u16 unk_36;
    /* 38 */ u16 value38;
    /* 3a */ u16 value3a;
    /* 3c */ u8 player;
} MenuSoundObj;

// One entry of the 16-entry pool at +0xb4 of the pool object (entries are 0x18 bytes apart). The id is -1 when free.
typedef struct MenuPoolEntry {
    /* 00 */ u32 unk_00; // object cleared by Menu_ClearRef (its nonzero value marks the entry as in use)
    /* 04 */ s32 id;
    /* 08 */ u32 unk_08;
    /* 0c */ u32 unk_0c;
    /* 10 */ u8 unk_10[8];
} MenuPoolEntry;

// The pool object: a count at +8, the entries at +0xb4, and a current index at +0x240.
typedef struct MenuPool {
    /* 00 */ s32 ready; // set to 1 by Menu_InitPool, tested by Menu_UpdatePool
    /* 04 */ u8 unk_04[0x8 - 0x4];
    /* 08 */ s32 count;
    /* 0c */ s32 unk_0c;
    /* 10 */ u8 unk_10[0xb4 - 0x10];
    /* 0b4 */ MenuPoolEntry entries[16];
    /* 234 */ u8 unk_234[0x240 - 0x234];
    /* 240 */ s32 current;
} MenuPool;

extern u8 data_02127178[];
extern u8 data_02127180[];
extern u16 data_020df004[];

extern "C" {
s32 func_020be128(void *ref);
void RectSpan_callAndMore(s32 value, void *data, void *obj, void *ref);
void func_020ba948(void *obj, s32 value);
void func_020bf09c(void *out, void *data, void *obj);
void OS_GetOwnerInfoEx(void *info);
extern "C" s32 Ctrl_isReady(void *obj);
s32 func_020be5a4(MenuList *list, s32 delta);
MenuPoolEntry *Menu_AllocPoolEntry(MenuPool *pool, s32 flag);
void func_020bf9dc(void *obj, s32 a, s32 b);
void SndState_StartEntryList(void *obj, s32 a, s32 b);
void SndSlot_ReleaseFirst(void *obj, s32 value);
void Work21_clear(void *buf);
void lobby_callWithZeroPos(s32 active, void *buf);
void func_020bc6c4(void *obj);
void func_020c2c48(void *arg, void *obj);
s32 func_020bc588(s32 value);
void func_020bc84c(s32 obj, void *checker, void *a, void *b, void *c, u16 d);
s32 func_020bb450(void *obj);
s32 func_020bb56c(void *obj);
s32 Ctrl_tryChange(void *obj, u8 *out);
s32 Ctrl_updateAd(void *obj);
}

void Menu_GetRect(s16 *rect, s32 unused); // C++, src/game/menu_8.cpp

#endif
