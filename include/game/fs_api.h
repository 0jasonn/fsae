#ifndef GAME_FS_E_API_H
#define GAME_FS_E_API_H

// Functions defined in src/game/fs_e*.cpp.

#include "engine/entity.h"

extern "C" {
void fsCopyFile(u8 srcSlot, u8 dstSlot);
void fsDeleteFile(u8 slot);
s32 fsFileCheck(u8 slot);
u8 fsFileCount(void);
void fsLoadFiles(void);
void fsSaveBegin(void);
void fsSaveEnd(void);
void fsUpdateStatus(u8 slot);
}

#endif
