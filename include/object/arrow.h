#ifndef WIP_E_ARROW_H
#define WIP_E_ARROW_H

// Arrow / beam module (src/game/arrow.cpp). Callees that functions.h does not declare yet, with their dsd names.
// The reviewer moves the ones with an original name into functions.h.
#include "engine/functions.h"

void func_020841b0(Entity *e);
void func_02086168(Entity *e);

#include "object/template.h"

// Beam-only fields that Entity does not name (file-local overlay on unk_64).
typedef struct BeamVars {
    u8 unk_00[0x64];
    s32 lifetime; // 0x64: counts down each frame; the beam is removed at 0
} BeamVars;

#endif
