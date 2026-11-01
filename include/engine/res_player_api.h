#ifndef ENGINE_RES_PLAYER_API_H
#define ENGINE_RES_PLAYER_API_H

// Functions defined in src/engine/res_player*.cpp.

#include "engine/entity.h"

extern "C" {
void ResDraw_Reset(u8 *draw);
void ResDraw_SetModeAndReset(u8 *draw, u32 mode);
void ResDraw_SetPos(u8 *draw, u32 x, u32 y);
void ResDraw_SetPriority(u8 *draw, u32 value);
void ResDraw_SetSize(u8 *draw, s32 width, s32 height);
void ResPlayer_Refresh(u8 *player);
void ResPlayer_SetCursorTableAndRefresh(u8 *player, u8 *cursorTable);
void ResPlayer_Start(u8 *player, u8 *cursorTable, u8 *entryTable);
}

#endif
