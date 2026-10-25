#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Table of little-endian words: the entry count at +0 and the bytes from +0xc.
typedef struct WordTable {
    u32 count;
    u32 unk_04;
    u32 unk_08;
    u8 *data;
} WordTable;

extern "C" s32 func_0200c594(void *self, u32 value, u32 *out);
extern "C" s32 WordTable_Scan(void *self, WordTable *table);

// WordTable_Scan(self, table) (0x0200c09c): passes each little-endian word of the table to func_0200c594 with a stack word
// as the out argument. The first nonzero result stops the scan and is returned as 1; otherwise 0.
ARM s32 WordTable_Scan(void *self, WordTable *table) {
    u8 *entry;
    u32 i;
    u32 value;
    u32 out;

    entry = table->data;
    for (i = 0; i < table->count; i++) {
        value = entry[0] | (entry[1] << 8) | (entry[2] << 16) | (entry[3] << 24);
        if (func_0200c594(self, value, &out) != 0) {
            return 1;
        }
        entry += 4;
    }
    return 0;
}
