#ifndef GAME_KNIFEINFO_API_H
#define GAME_KNIFEINFO_API_H

// Functions defined in src/game/knifeinfo*.cpp.

#include "engine/entity.h"

extern "C" {
s32 Knife_Message_KnifeInfoGetter_getVariable(const void *a, s32 index);
}

#endif
