#ifndef GAME_KEYCLEAR_API_H
#define GAME_KEYCLEAR_API_H

// Functions defined in src/game/keyclear*.cpp.

#include "engine/entity.h"

extern "C" {
void CircleWindowHook(void);
void EffectWindowHook(void);
void keyClear(void);
}

void InitCircleWindow(u16 a, u16 b);                    // InitCircleWindow(unsigned short, unsigned short), 0x0202b5d4
void StopEffectWindow(void);                            // StopEffectWindow(), 0x0202b598

#endif
