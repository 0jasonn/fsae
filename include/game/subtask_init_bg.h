#ifndef GAME_SUBTASK_INIT_BG_H
#define GAME_SUBTASK_INIT_BG_H

#include "engine/entity.h"

// Chunk object as opened by ResChunk_OpenTTLP / ResChunk_GetNRCS (slots b and c): size at 0x08, data at 0x0c.
typedef struct SubtaskNrcsChunk {
    u8 unk_00[0x8];
    u32 size;
    void *ptr;
} SubtaskNrcsChunk;

// Chunk object as opened by ResChunk_OpenRACH2 (slot a): size at 0x10, data at 0x14.
typedef struct SubtaskRachChunk {
    u8 unk_00[0x10];
    u32 size;
    void *ptr;
} SubtaskRachChunk;

#endif
