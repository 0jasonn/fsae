#ifndef GAME_ITEM_ROW_API_H
#define GAME_ITEM_ROW_API_H

// Functions defined in src/game/item_row*.cpp.

#include "engine/entity.h"

extern "C" {
void ItemRow_layout(void *selfv, s32 arg, s16 *pos);
}

#endif
