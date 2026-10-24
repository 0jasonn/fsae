#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"

// Subtask send stop, 0x0209dbc8 to 0x0209dc24: clears the transfer queues and two status words.

extern u8 data_0217a23c[];
extern u8 data_0217c23c[];
extern u8 data_0217d23c[];

// subTaskSendStop (0x0209dbc8): clears the transfer queues and the two status words.
ARM void subTaskSendStop(void) {
    u32 i;

    for (i = 0; i < 4; i++) {
        *(u32 *)(data_0217a23c + i * 12 + 0x2f7c) = 0;
        *(u32 *)(data_0217a23c + i * 4 + 0x3014) = 0;
    }
    *(u32 *)(data_0217c23c + 0xfac) = 0;
    *(u32 *)(data_0217c23c + 0xfe0) = 0;
    *(u32 *)(data_0217d23c + 0xb4) = 0;
}
