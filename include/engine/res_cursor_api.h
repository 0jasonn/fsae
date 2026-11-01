#ifndef ENGINE_RES_CURSOR_API_H
#define ENGINE_RES_CURSOR_API_H

// Functions defined in src/engine/res_cursor*.cpp.

#include "engine/entity.h"

extern "C" {
void ResCursor_Clear(u8 *cursor);
s32 ResCursor_Seek(u8 *cursor, u32 index);
s32 ResCursor_SeekAndReset(u8 *cursor, u32 index);
s32 ResCursor_SetTableAndInit(u8 *cursor, u8 *table);
void ResPlayer_Init(u8 *player);
u32 ResRef_GetWord(u8 *ref);
void VramObj_Copy16(const void *src, u32 dst, u32 size);
void VramObj_Copy16Offset(const void *src, u32 dst, u32 size);
}

#endif
