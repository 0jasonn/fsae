#include "engine/functions.h"
#include "global.h"

// zMalloc / zFree module. The block table at data_0213a7a0 holds a u16 entry count, followed by 4-byte entries
// {u16 start, u16 end} (offsets from the table base). zMalloc (0x0202a39c, not matched yet) allocates below the heap
// top data_0213cfa0 and belongs before zFree in this file.
//   zFree (0x0202a568): removes the entry whose start is the block offset, moving the last entry into its place.

extern u8 data_0213a7a0[];

// zFree (0x0202a568)
ARM void zFree(void *block) {
    u16 *table = (u16 *)data_0213a7a0;
    u16 i = 0;
    u16 count = table[0];
    u16 *entry = table + 1;
    u16 offset = (u16)((u8 *)block - (u8 *)table);

    for (; i < count; i++) {
        if (entry[0] == offset) {
            u16 *tbl = (u16 *)data_0213a7a0;
            u16 *last = (u16 *)data_0213a7a0 - 1 + count * 2;
            entry[0] = last[0];
            last[0] = 0;
            entry[1] = last[1];
            last[1] = 0;
            count--;
            tbl[0] = count;
            return;
        }
        entry += 2;
    }
}
