#ifndef GAME_MESSAGESELECT_API_H
#define GAME_MESSAGESELECT_API_H

// Functions defined in src/game/messageselect*.cpp.

#include "engine/entity.h"

extern "C" {
void Knife_Message_MessageSelect_init(void *a);
void Knife_Message_MessageSelect_update(void *self);
}

#endif
