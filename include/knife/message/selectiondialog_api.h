#ifndef GAME_SELECTIONDIALOG_API_H
#define GAME_SELECTIONDIALOG_API_H

// Functions defined in src/game/selectiondialog*.cpp.

#include "engine/entity.h"

extern "C" {
void Knife_Message_selectionDialog_close(void *a);
BOOL Knife_Message_selectionDialog_isModal(const void *a);
void Knife_Message_selectionDialog_stop(void *a);
BOOL Knife_Message_selectionDialog_update_close(void *a);
BOOL Knife_Message_selectionDialog_update_open(void *a);
}

#endif
