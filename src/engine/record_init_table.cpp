#include "engine/functions.h"
#include "global.h"

extern "C" u8 data_020df12c[];
extern "C" void Record_Init(u8 *self, u32 a, u32 b, u32 c, u32 d, u32 e, u32 f);

// Record_InitTable (provisional name): Record_Init with the table data_020df12c as e and b as f.
extern "C" void Record_InitTable(u8 *self, u32 a, u32 b, u32 c, u32 d);
ARM void Record_InitTable(u8 *self, u32 a, u32 b, u32 c, u32 d) {
    Record_Init(self, a, b, c, d, (u32)data_020df12c, b);
}
