#ifndef GAME_BACKUP_API_H
#define GAME_BACKUP_API_H

#include "engine/entity.h"

s8 ReadCartInfo(u32 *data);                 // ReadCartInfo(unsigned long*), 0x02056188 (src/game/backup.cpp)

s32 Knife_writeHeaderBlock(const u32 *data); // 0x02056174 (src/game/backup.cpp)

s32 Knife_getSaveBuffer(void);

#endif
