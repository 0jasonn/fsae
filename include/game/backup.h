#ifndef GAME_BACKUP_H
#define GAME_BACKUP_H

#include "engine/entity.h"

// data_02171d10: save load state. +04 set once a file is in the save buffer, +08 its length.
typedef struct SaveLoadState {
    void *unk_00;
    u32 loaded;
    u32 fileLength;
} SaveLoadState;

#endif
