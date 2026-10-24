#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"

extern u8 data_0217a23c[];
extern u8 data_0217a46c[];
extern u8 data_0217d06c[];
extern "C" void MI_CpuFill8(void *dst, u8 value, u32 size);

// func_0209bee4 (0x0209bee4): clears the 0x80 bytes at data_0217d06c
extern "C" void func_0209bee4(void);
ARM void func_0209bee4(void) {
    MI_CpuFill8(data_0217d06c, 0, 0x80);
}
