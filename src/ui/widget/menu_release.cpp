#include "engine/functions.h"
#include "ui/widget/ctrl_free_api.h"
#include "ui/widget/ctrl_free_virtual_api.h"
#include "engine/packed_set_api.h"
#include "ui/widget/menu.h"
#include "ui/widget/menu_release.h"

// Menu_releaseBlocks (0x020bc6c4): resets the menu, frees the blocks it holds (the two at +0x34c, then the ones at
// +0x348, +0x35c, +0x344 and +0x340, through a holder cell that starts with the menu pointer), frees the blocks at
// +0x14 and +0x10 on the menu heap, and runs the cleanup calls of the sub-objects. Returns the menu.
MenuWork *Menu_releaseBlocks(MenuWork *menu) {
    void *holder;
    s32 i;

    Menu_Reset(menu);
    holder = menu;
    for (i = 0; i < 2; i++) {
        Ctrl_freeVirtualBlockB(&holder, *(void **)((u8 *)menu + 0x34c + i * 4));
    }
    Ctrl_freeSpanBlock(&holder, *(void **)((u8 *)menu + 0x348));
    Ctrl_freeVirtualBlock(&holder, (s32)*(void **)((u8 *)menu + 0x35c));
    Ctrl_freeBlock(&holder, *(void **)((u8 *)menu + 0x344));
    Ctrl_freeBlock(&holder, *(void **)((u8 *)menu + 0x340));
    if (*(void **)((u8 *)menu + 0x14) != NULL) {
        Heap_VirtualFree(menu, *(void **)((u8 *)menu + 0x14));
    }
    if (*(void **)((u8 *)menu + 0x10) != NULL) {
        Heap_VirtualFree(menu, *(void **)((u8 *)menu + 0x10));
    }
    Packed_noop((u8 *)menu + 0x40500);
    Packed_noop((u8 *)menu + 0x403f8);
    ((void (*)(void *))Menu_NoOp)((u8 *)menu + 0x40370);
    ((void (*)(void *))Menu_NoOp2)((u8 *)menu + 0xfc);
    return menu;
}
