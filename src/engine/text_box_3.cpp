#include "engine/functions.h"
#include "global.h"

extern "C" u8 data_020df164[];

// TextBox_LookupTable (provisional name): the word in the 16-byte row at data_020df164 + self[1] * 16, indexed by self[0].
extern "C" u32 TextBox_LookupTable(u8 *self);
ARM u32 TextBox_LookupTable(u8 *self) {
    u8 *row;

    row = data_020df164 + self[1] * 16;
    return ((u32 *)row)[self[0]];
}
