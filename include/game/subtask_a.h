#ifndef WIP_A_SUBTASK_A_H
#define WIP_A_SUBTASK_A_H

#include "engine/functions.h"

// Functions and work blocks the implementer A subtask files share (original C names where the symbols are plain).

// Work block of the subtask screens (pointer at data_0217d348); only the fields used by these files are named.
typedef struct SubtaskPushStartWork {
    u8 unk_00[0x51c];
    s32 phase;         // 0x51c: 0 while waiting for a press, then 1 and up
    u8 unk_520[0xc];
    u32 frameCount;    // 0x52c
    s32 blinkCount;    // 0x530
} SubtaskPushStartWork;

extern "C" void GXS_SetGraphicsMode(u32 mode);
extern "C" void func_02015084(u32 a);
extern "C" void func_02015190(u32 a);
extern "C" void subTaskSetBG0Offset_reset(void);
extern "C" void subTaskSetBG1Offset_reset(void);
extern "C" void subTaskSetBG2Offset_reset(void);
extern "C" void subTaskSetBG3Offset_reset(void);
// Hex text helpers of the subtask screens (0x0209ae98 integrated in src/game/subtask_work_hex.cpp; the tile mapping in
// src/wip/A/subtask_char_tile.cpp). subtask_hex_ascii_work returns the digit count written by hex_ascii_chg0.
extern "C" s32 subtask_hex_ascii_work(s32 a, s32 b, u32 c);
extern "C" u32 subtask_char_tile_num(u32 c);
extern "C" u32 subtask_char_tile_num_alt(u32 c);
int is_op_demo_end(void); // C++ name _Z14is_op_demo_endv, 0x020510f0

#endif
