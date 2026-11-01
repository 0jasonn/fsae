#ifndef GAME_LOBBY_API_H
#define GAME_LOBBY_API_H

// Functions defined in src/game/lobby*.cpp.

#include "engine/entity.h"

extern "C" {
void lobby_freeBlock(void *heap, void *block);
void lobby_msgObj_release(void *obj, void *heap);
s32 lobby_selection_dialogUpdate(void);
void lobby_setRecvParam(s32 index, s32 flag, s32 value);
void lobby_stepAndCall(void *self, void *arg);
s32 lobby_updateNone(void);
void subTask_lobby_end(void);
s32 update_change_filesel(void);
}

#endif
