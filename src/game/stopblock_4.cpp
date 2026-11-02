#include "engine/functions.h"
#include "actor/enemy/em12.h"
#include "game/stopblock_4.h"

// Functions in this file (original names from the debug build):
//   sbRegistSub (0x0204e7d4)

// sbRegistSub(key, kind, begin, end) (0x0204e7d4): finds the first free stop block in [begin, end) and fills it
// from the key words of the caller (cell x and y in the low 10 bits of key[2] and key[3]), the offsets of the kind
// and the flag bits. Returns 1 when a block was registered, 0 when none was free.
int sbRegistSub(u16 *key, u8 kind, STOPBLOCK_WORK_ *begin, STOPBLOCK_WORK_ *end) {
    STOPBLOCK_WORK_ *block;
    u8 keyHi;
    u8 keyLo;
    int rowBits;
    int colBits;

    keyHi = key[1] >> 8;
    keyLo = key[1] & 0xff;
    for (block = begin; block < end; block++) {
        if (block->key == 0) {
            rowBits = (u16)((key[3] & 0x3ff) + em12_spawnOffsetY[kind * 2]);
            colBits = (u16)((key[2] & 0x3ff) + data_0213492c[kind * 2]);
            block->key = (colBits >> 4) | ((rowBits >> 4) << 6);
            if (key[2] & 0xc00) {
                block->key |= (key[2] & 0xc00) << 4;
            } else {
                block->key |= func_0208af18(block->key) ? 0x8000 : 0x4000;
            }
            block->key |= (kind != 0) ? 0x1000 : 0;
            block->state = keyHi;
            block->unk_03 = keyLo;
            return 1;
        }
    }
    return 0;
}
