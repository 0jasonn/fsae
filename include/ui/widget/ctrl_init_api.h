#ifndef ENGINE_CTRL_INIT_API_H
#define ENGINE_CTRL_INIT_API_H

// Functions defined in src/engine/ctrl_init*.cpp.

#include "engine/entity.h"

extern "C" {
void Ctrl_initA(void *selfv, void *arg);
void Ctrl_initB(void *selfv, void *arg);
}

#endif
