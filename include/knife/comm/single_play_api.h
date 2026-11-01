#ifndef ENGINE_SINGLE_PLAY_API_H
#define ENGINE_SINGLE_PLAY_API_H

// Functions defined in src/engine/single_play*.cpp.

#include "engine/entity.h"

extern "C" {
void Knife_Single_SinglePlay_ChangeContPlayer(void *self);
void Knife_Single_SinglePlay_ChangeContPlayerDirect(void *self);
void Knife_Single_SinglePlay_ChangeFormationNo(void *self);
void Knife_Single_SinglePlay_InitializeCont(void *self);
void Knife_Single_SinglePlay_InitializeFormation(void *self);
void Knife_Single_SinglePlay_SetContNoDirect(void *self, u8 no);
void Knife_Single_SinglePlay_SetFormationNo(void *self, u8 no);
void Knife_Single_SinglePlay_SetFormationNoDirect(void *self, u8 no);
}

#endif
