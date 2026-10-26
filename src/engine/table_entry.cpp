#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_f.h"

// table_entry: function Table_getEntry58 (0x020bc260), provisional name.

// Table_getEntry58(self, index) (0x020bc260, provisional name): the entry at index of the table at +0x14 (0x58 bytes each)
// while index is below the count at +0x2c14, otherwise NULL
extern "C" void *Table_getEntry58(u8 *self, s32 index);
ARM void *Table_getEntry58(u8 *self, s32 index) {
    s32 count;

    count = *(s32 *)(self + 0x2c14);
    if (index < count) {
        return self + 0x14 + index * 0x58;
    }
    return NULL;
}
