#include "engine/functions.h"
#include "engine/pair_block.h"
#include "global.h"
#include "types.h"

typedef struct PairBuffer {
    u8 unk_00[0xc];
    u16 field_0c;
    u16 field_0e;
    u8 unk_10[4];
    u8 record[1];
} PairBuffer;

extern "C" void MI_CpuFill8(void *dst, u8 value, u32 size);
extern "C" void Pair_Setup(void *buf, s32 n);

// Pair_Setup(buf, n) (0x02019b00): clears the 0x300 byte buffer and sets the pair block up on it with flags 3.
// The cursor starts at the record (+0x14), and the field at +0xc is 0x2ec - n.
ARM void Pair_Setup(void *buf, s32 n) {
    data_02129cac.pair = buf;
    MI_CpuFill8(buf, 0, 0x300);
    data_02129cac.flags = 3;
    ((PairBuffer *)data_02129cac.pair)->field_0c = 0x2ec - n;
    ((PairBuffer *)data_02129cac.pair)->field_0e = 0;
    data_02129cac.cursor = ((PairBuffer *)data_02129cac.pair)->record;
    ((PairBuffer *)data_02129cac.pair)->record[0] = 0;
    data_02129cac.cursor[1] = 0;
}
