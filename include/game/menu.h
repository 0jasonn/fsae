#ifndef WIP_G_MENU_H
#define WIP_G_MENU_H

#include "engine/functions.h"
#include "global.h"

// Provisional module name for the unnamed UI state code at 0x020bcd34 onward (a guess from the state table and the
// touch input handling; not confirmed against the debug names).

// Object with a virtual check in vtable slot 0. func_020c2c34(obj, id) calls obj->Check(id).
struct MenuChecker {
    virtual s32 Check(s32 id);
};

// Input record passed to the menu update (bytes 5 and 6 are request flags).
typedef struct MenuInput {
    /* 00 */ u8 unk_00[5];
    /* 05 */ u8 flag5;
    /* 06 */ u8 flag6;
} MenuInput;

// Event filled in by func_020ba9a4: a kind and a value.
typedef struct MenuEvent {
    /* 00 */ u16 kind;
    /* 02 */ u16 value;
} MenuEvent;

// Event filled in by func_020b8554: a kind and two bytes.
typedef struct MenuEventB {
    /* 00 */ u16 kind;
    /* 02 */ u8 a;
    /* 03 */ u8 b;
} MenuEventB;

// Sub-object at 0x40000 of the menu object. Each field is placed by its comment offset (checked with probes).
typedef struct MenuSub {
    /* 000 */ u8 unk_000[0x370];
    /* 370 */ u8 unk_370[8]; // object passed to func_020be518 and Menu_SetActive
    /* 378 */ void *unk_378; // points at the table at 0xf0
    /* 37c */ u8 unk_37c[0x398 - 0x37c];
    /* 398 */ u8 unk_398;
    /* 399 */ u8 unk_399[0x39c - 0x399];
    /* 39c */ s32 unk_39c; // pending reset (Menu_Reset)
    /* 3a0 */ u8 unk_3a0[0x3f8 - 0x3a0];
    /* 3f8 */ u8 unk_3f8[0x608 - 0x3f8]; // object passed to func_020bdd60
    /* 608 */ s32 unk_608;
    /* 60c */ u8 unk_60c[0x616 - 0x60c];
    /* 616 */ u16 unk_616[3];
    /* 61c */ u16 unk_61c;
    /* 61e */ s16 state; // 0 = idle, 1 = active, 2 = set by flag5 (provisional)
    /* 620 */ u8 unk_620;
    /* 621 */ u8 unk_621; // set by Menu_Finish
} MenuSub;

// Object at 0x358 of the menu. Only the byte at 0xad is used here (it disables the blend setup when set).
typedef struct MenuObj {
    /* 00 */ u8 unk_00[0xad];
    /* ad */ u8 flagAd;
} MenuObj;

// Object at 0x364 of the menu: a view with a vtable. Slot 2 takes a position (x at +0, y at +2).
struct MenuView {
    virtual void Slot0(void);
    virtual void Slot1(void);
    virtual void SetPos(s16 *pos);
    s16 posX; // at +4, not a member of the vtable
};

// A list-like object (scroll state). Offsets are from the original code.
typedef struct MenuList {
    /* 00 */ u32 unk_00;
    /* 04 */ u32 active; // nonzero when the list is active
    /* 08 */ u32 unk_08;
    /* 0c */ s16 unk_0c;
    /* 0e */ s16 unk_0e;
    /* 10 */ u32 unk_10;
    /* 14 */ s16 unk_14;
    /* 16 */ s16 unk_16;
    /* 18 */ u32 unk_18;
    /* 1c */ s16 unk_1c;
    /* 1e */ s16 unk_1e;
    /* 20 */ s16 unk_20;
    /* 22 */ s16 unk_22;
    /* 24 */ s16 unk_24;
    /* 26 */ s16 unk_26;
    /* 28 */ u8 unk_28;
} MenuList;

// Nine four-halfword cells followed by a few flags (cleared by Menu_ClearCells).
typedef struct MenuCell {
    /* 0 */ u16 f0;
    /* 2 */ u16 f2;
    /* 4 */ u16 f4;
    /* 6 */ u16 f6;
} MenuCell;

typedef struct MenuCellWork {
    /* 00 */ MenuCell cells[9];
    /* 48 */ u8 flag48;
    /* 49 */ u8 flag49;
    /* 4a */ u8 flag4a;
    /* 4b */ u8 unk_4b;
    /* 4c */ u16 h4c;
    /* 4e */ u16 h4e;
} MenuCellWork;

// The menu object.
typedef struct MenuWork {
    /* 000 */ MenuChecker *checker;
    /* 004 */ u8 unk_004[0xf0 - 0x004];
    /* 0f0 */ void *unk_0f0[3];
    /* 0fc */ u8 unk_0fc[0x354 - 0x0fc];
    /* 354 */ void *unk_354;
    /* 358 */ MenuObj *unk_358; // object with a flag byte at 0xad
    /* 35c */ u8 unk_35c[0x360 - 0x35c];
    /* 360 */ void *unk_360;
    /* 364 */ MenuView *unk_364;
    /* 368 */ u8 unk_368[0x40000 - 0x368];
    /* 40000 */ MenuSub sub;
} MenuWork;

extern u8 data_02127188[];

// Wrapper object whose first word is a menu pointer (used by Menu_RunFromWrapper).
typedef struct MenuWrapper {
    MenuWork *ptr;
} MenuWrapper;

extern "C" {
void func_02013d28(s32 a, s32 b, s32 c, s32 d);
void func_02013c6c(s32 a, s32 b, s32 c, s32 d);
s32 func_020c2c34(MenuChecker *obj, s32 id);
s32 func_020ba004(s32 value);
s32 func_020ba9a4(void *obj, MenuEvent *event, MenuInput *input);
s32 func_020b8554(void *obj, MenuEventB *event, MenuInput *input);
s32 lobby_msgObj_init(s32 value);
s32 func_020b8784(s32 value);
s32 func_020bbb78(s32 value);
s32 func_020bbf54(s32 value);
s32 func_020bac20(void *obj);
s32 func_020bac58(void *obj);
void func_020bb70c(void *obj);
void func_020bc7b8(void *self, s32 value);
void func_020bc3a8(s32 value);
void func_020bbbfc(void *obj, s32 a, s32 b);
void func_020bdd60(MenuWork *menu, const void *data, void *obj, s32 flag);
s32 Menu_GetPosition(void *obj);
void *Menu_AcquirePoolEntry(void *pool, s32 id, s32 value); // src/game/menu_29.cpp (pool is a MenuPool, see game/menu_wip.h)
void func_020be518(void *obj, u8 a, u8 b);
void Menu_Finish(MenuWork *menu);
void Menu_UpdateView(MenuWork *menu, s32 flag);
void Menu_Step(MenuWork *menu, s32 flag);
void Menu_SetCursorPos(MenuWork *menu);
void func_0201500c(s32 a);
void Vram_DisableBankTail(void);
void MIi_CpuClearFast(u32 value, void *dst, u32 size);
void Menu_Run(MenuWork *menu);
s32 func_020b8c00(s32 value);
void SND_SetMasterVolume(s32 volume);
void SndSys_StartActiveTimer(s32 a, s32 b, s32 c, s32 d);
void func_020bffd8(s32 a, s32 b, s32 c, s32 d);
void func_020c219c(s32 a, s32 b, s32 c, s32 d);
void func_020c2c78(s32 a, s32 b, s32 c, s32 d);

void TP_Init(void);
s32 TP_GetUserInfo(void *info);
void TP_SetCalibrateParam(void *info);
void TP_RequestAutoSamplingStartAsync(u32 a, u32 b, void *arg, u32 c);
void TP_WaitBusy(s32 mode);
s32 TP_CheckError(s32 mode);
void G2x_SetBlendBrightness_(u32 reg, s32 plane, s32 value);
void func_020b88dc(MenuView *view, s32 value);
void Menu_SyncScroll(MenuList *list);
void Menu_SyncListRect(MenuList *list);
s32 Menu_CountItems(MenuList *list, s32 value);
s32 lobby_copyBounds(s16 *out);
}

// Menu functions in this module. The unit that defines each one is named by the file in src/wip/G.
void Menu_Begin(MenuWork *menu);
void Menu_ResetScroll(MenuList *list);
void Menu_SetActive(MenuList *list, s32 value);
void Menu_StartTouch(void *callbackArg);
void Menu_Step(MenuWork *menu, s32 flag);

#endif
