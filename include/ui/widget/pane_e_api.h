#ifndef ENGINE_PANE_E_API_H
#define ENGINE_PANE_E_API_H

// Functions defined in src/engine/pane_e*.cpp.

#include "engine/entity.h"

extern "C" {
void Pane_calcRectPair(s16 *outA, s16 *outB, const s16 *a, const s16 *b, const s16 *c);
void Pane_tailCallCalc(void *self, void *unused, void *b, void *c);
}

#endif
