#ifndef ENGINE_MENU_INIT_H
#define ENGINE_MENU_INIT_H

#include "engine/functions.h"
#include "ui/widget/menu.h"

void Menu_ClearPair(u32 *pair);
void Menu_ClearList(MenuList *list);
void Menu_ClearCells(MenuCellWork *cells);

extern "C" {
void Obj_initVtableC(void *object);
u8 *Menu_InitState(u8 *self);
}

#endif
