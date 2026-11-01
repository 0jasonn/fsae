#ifndef GAME_CLAMP_API_H
#define GAME_CLAMP_API_H

// Functions defined in src/game/clamp*.cpp.

#include "engine/entity.h"

extern "C" {
void clamp_s8(signed char &value, signed char low, signed char high);
}

#endif
