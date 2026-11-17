#include "engine/functions.h"
#include "global.h"
#include "knife/subtask/subtask.h"

extern u8 data_0217a23c[];
extern u8 data_0217a46c[];
extern u8 data_0217d06c[];
extern "C" void MI_CpuFill8(void *dst, u8 value, u32 size);

// Reserves the first free cell. A full pool leaves the output index untouched and returns the pool base.
void *subTask_GetNewCellAnimation(s32 *outIndex) {
    u8 *result = data_0217a46c;
    s32 index = 0;

    do {
        // The occupancy array starts 0x2e30 bytes into the subtask work block.
        if (data_0217a23c[index + 0x2e30] == 0) {
            result += index * 0x58;
            *outIndex = index;
            data_0217a23c[index + 0x2e30] = 1;
            break;
        }
        index++;
    } while (index < 0x80);
    return result;
}

// func_0209bee4 (0x0209bee4): clears the 0x80 bytes at data_0217d06c
void func_0209bee4(void) {
    MI_CpuFill8(data_0217d06c, 0, 0x80);
}
