#ifndef KNIFE_MESSAGE_RENDERTARGET_API_H
#define KNIFE_MESSAGE_RENDERTARGET_API_H

// RenderTarget state and OBJ count helpers.

#include "engine/entity.h"

extern "C" {
void *Knife_Message_RenderTarget_dtor_RenderTarget_0a3160(void *self);
void Knife_Message_i_FinalizeRenderTargets(void);
void Knife_Message_RenderTarget_finalize(void *self);  // 0x020a4e8c
s32 func_020c61f4(s32 width, s32 height);
}

#endif
