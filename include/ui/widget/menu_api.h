#ifndef GAME_MENU_API_H
#define GAME_MENU_API_H

// Functions defined in src/game/menu*.cpp.

#include "engine/entity.h"

extern "C" {
void MenuSound_SetFade(void * volatile *ref, u16 value);
void MenuSound_SetFadeTimes(void * volatile *ref, u16 value, u16 value2);
void Menu_CreateEntryEx(void *out, void *checker, void *a, void *b, void *c, u16 d);
void Menu_SetRefByte40(void * volatile *ref, u8 value);
}

#endif
