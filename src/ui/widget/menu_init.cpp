#include "engine/functions.h"
#include "engine/menu_init_e.h"

// Menu_InitState (0x020bc588): clears the state of a menu object (counters, lists, cells, the two embedded objects
// and the tables of pointers) and returns it
u8 *Menu_InitState(u8 *self) {
    s32 i;
    s32 j;
    s32 k;

    *(s32 *)(self + 0x10) = 0;
    *(s32 *)(self + 0x14) = 0;
    *(u8 *)(self + 0x80) = 0;
    *(u8 *)(self + 0xec) = 0;
    Menu_ClearPair((u32 *)(self + 0xfc));
    *(s32 *)(self + 0x340) = 0;
    *(s32 *)(self + 0x344) = 0;
    *(s32 *)(self + 0x348) = 0;
    *(s32 *)(self + 0x354) = 0;
    *(s32 *)(self + 0x358) = 0;
    *(s32 *)(self + 0x35c) = 0;
    *(s32 *)(self + 0x360) = 0;
    Menu_ClearList((MenuList *)(self + 0x40370));
    *(s32 *)(self + 0x4039c) = 0;
    *(u16 *)(self + 0x403a0) = 0;
    *(u16 *)(self + 0x403a2) = 0;
    *(u16 *)(self + 0x403a4) = 0;
    Menu_ClearCells((MenuCellWork *)(self + 0x403a6));
    Obj_initVtableC(self + 0x403f8);
    Obj_initVtableC(self + 0x40500);
    *(s32 *)(self + 0x40608) = 0;
    *(u16 *)(self + 0x4060c) = 0;
    *(u16 *)(self + 0x4060e) = 0;
    *(u16 *)(self + 0x40610) = 0;
    *(u16 *)(self + 0x40612) = 0;
    *(u16 *)(self + 0x40614) = 0;
    *(u16 *)(self + 0x4061c) = 0;
    *(u16 *)(self + 0x4061e) = 0;
    *(u8 *)(self + 0x40620) = 0;
    *(u8 *)(self + 0x40621) = 0;
    *(u8 *)(self + 0x40622) = 0;
    *(u8 *)(self + 0x40623) = 0;
    *(u8 *)(self + 0x40624) = 0;
    for (i = 0; i < 3; i++) {
        *(s32 *)(self + 0xf0 + i * 4) = 0;
    }
    for (j = 0; j < 2; j++) {
        *(s32 *)(self + 0x34c + j * 4) = 0;
    }
    for (k = 0; k < 2; k++) {
        *(s32 *)(self + 0x364 + k * 4) = 0;
    }
    return self;
}
