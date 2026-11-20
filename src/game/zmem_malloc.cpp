#include "engine/functions.h"
#include "game/zmem.h"
#include "global.h"

// zMalloc (0x0202a39c): first-fit allocator over the block table at data_0213a7a0 (u16 entry count, then {u16 start,
// u16 end} records, offsets from the table base). It tries the block ending at the heap top data_0213cfa0 first and
// otherwise places the block just below an existing one; the new block is cleared. Returns NULL if nothing fits.
extern u8 data_0213a7a0[];
extern u8 data_0213cfa0[];

void *zMalloc(u16 size) {
    u8 *top = data_0213cfa0;
    u8 *bs;
    u16 *table = (u16 *)data_0213a7a0;
    u16 i;
    u8 *base = data_0213a7a0;
    u8 *cand;
    u16 k;
    int fits = 1;
    u16 count = table[0];
    u8 *be;
    u8 *limit;
    u8 *bstart;
    u16 j;
    size = (u16)((size + 3) & 0xfffc);
    cand = top - size;

    {
        for (i = 0; i < count; i++) {
            bs = base + table[i * 2 + 1];
            be = base + table[i * 2 + 2];
            if (bs <= cand && cand <= be) {
                fits = 0;
                break;
            }
            if (bs <= top && top <= be) {
                fits = 0;
                break;
            }
            if (bs <= cand && top <= be) {
                fits = 0;
                break;
            }
            if (cand <= bs && be <= top) {
                fits = 0;
                break;
            }
        }
    }

    if (!fits) {
        limit = (u8 *)(table + 3 + count * 2);
        k = 0;
        do {
            bstart = data_0213a7a0 + table[k * 2 + 1];
            cand = bstart - size;
            fits = 0;
            if (cand < limit) {
                continue;
            }
            fits = 1;
            for (j = 0; j < count; j++) {
                bs = data_0213a7a0 + table[j * 2 + 1];
                be = data_0213a7a0 + table[j * 2 + 2];
                if (bs <= cand && cand < be) {
                    fits = 0;
                    break;
                }
                if (bs < bstart && bstart <= be) {
                    fits = 0;
                    break;
                }
                if (bs <= cand && bstart <= be) {
                    fits = 0;
                    break;
                }
                if (cand <= bs && be <= bstart) {
                    fits = 0;
                    break;
                }
            }
            if (fits) {
                break;
            }
        } while (k++, k < count);
    }

    if (!fits) {
        return 0;
    }
    ((u16 *)data_0213a7a0)[count * 2 + 1] = (u16)(cand - data_0213a7a0);
    ((u16 *)data_0213a7a0)[count * 2 + 2] = (u16)(cand - data_0213a7a0 + size);
    ((u16 *)data_0213a7a0)[0] = count + 1;
    MemClearFast(cand, size);
    return cand;
}
