#ifndef GAME_RENDERTARGET_API_H
#define GAME_RENDERTARGET_API_H

// Functions defined in src/game/rendertarget*.cpp.

#include "engine/entity.h"

extern "C" {
void *Knife_Message_RenderTarget_dtor_RenderTarget_0a3160(void *self);
void Knife_Message_i_FinalizeRenderTargets(void);
void Knife_Message_RenderTarget_finalize(void *self);  // 0x020a4e8c
}

#endif
