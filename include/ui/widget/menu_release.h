#ifndef WIP_F_MENU_RELEASE_H
#define WIP_F_MENU_RELEASE_H

// Menu cleanup helpers near 0x020bc6c4 (provisional names).

#include "engine/functions.h"
#include "ui/widget/menu.h"

extern "C" {
MenuWork *Menu_releaseBlocks(MenuWork *menu);
void Heap_VirtualFree(void *heap, void *block);
}

// Subobject cleanup entry points (C++ linkage: the original names are mangled; defined in menu_8.cpp and menu_11.cpp).
void Menu_Reset(MenuWork *menu);
void Menu_NoOp(void);
void Menu_NoOp2(void);

#endif
