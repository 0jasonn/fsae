#include "engine/functions.h"
#include "global.h"
#include "engine/record_init_api.h"
#include "engine/record_init_sized_api.h"

extern "C" u8 data_020df120[];

// Record_InitSized (provisional name): Record_Init with the table data_020df120 as e and a size of 0x20 when d is 4, else 0x10.
void Record_InitSized(u8 *self, u32 a, u32 b, u32 c, u32 d) {
    u32 size;

    size = 0x20;
    if (d != 4) {
        size = 0x10;
    }
    Record_Init(self, a, b, c, d, (u32)data_020df120, size);
}
