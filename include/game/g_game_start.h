#ifndef WIP_G_GAME_START_H
#define WIP_G_GAME_START_H

// Game start subtask (subTask_game_start_*, 0x020c70ac to 0x020c75a4). Provisional names for the work block
// that data_02186fdc points at (its storage is data_02186fe0, 0x6c bytes).

#include "engine/functions.h"
#include "game/subtask.h"

// Work block of the game start subtask. The first 0x24 bytes are an OBJInfo (freed by subTask_free_objinfo).
typedef struct GameStartWork {
    /* 00 */ OBJInfo info;
    /* 24 */ u8 unk_24[0x3c];
    /* 60 */ u8 *cells; // 0x58-byte records, one per cellCount
    /* 64 */ s8 cellCount;
    /* 65 */ u8 flag65;
    /* 66 */ u8 unk_66[2];
    /* 68 */ u8 *buffer600; // 0x600 bytes, sent to VRAM by subTaskSendScr
} GameStartWork;

// Work block at data_02186fe0, reached through the pointer data_02186fdc.
extern GameStartWork data_02186fe0;
extern GameStartWork *data_02186fdc;

// Object at the pointer data_0217d348 (the OAM work block of the game over screen): the frame counter at +0x52c
// and a second counter at +0x530 are cleared on entry to the start subtask.
extern u8 *data_0217d348;

// BG offset resets (C++ signatures in original_names.tsv)
void subTaskSetBG0Offset_reset(void);
void subTaskSetBG1Offset_reset(void);
void subTaskSetBG2Offset_reset(void);

// Calls the start subtask makes into other units (C linkage: no signature in original_names.tsv)
extern "C" {
void GXS_SetGraphicsMode(u32 mode);
void func_02015084(u32 a);
void func_02015190(u32 a);
void *func_0208e148(u32 size);
}

// Calls made by the ending and error subtasks (original signatures in original_names.tsv)

// Function tables of the boot and terminate error screens (indexed by the byte at data_0212c500)
typedef void (*SubtaskFunc)(void);
extern u8 data_0212c500[];
extern u8 data_0217a258[];
extern SubtaskFunc data_021271cc[];
extern SubtaskFunc data_0212720c[];

extern "C" {
void func_020a3778(u32 a);
}

#endif
