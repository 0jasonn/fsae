#ifndef GAME_DEMO_API_H
#define GAME_DEMO_API_H

// Functions defined in src/game/demo*.cpp.

#include "engine/entity.h"

extern "C" {
void DemoTask(void);
int demoWaitCk(void);
}

#endif
