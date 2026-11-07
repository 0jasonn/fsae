#include "engine/functions.h"
#include "global.h"
#include "actor/object/k_bitstream.h"

// BitStream_ReadBits (provisional name): reads bits from the stream record. The record holds the byte cursor at +0, the
// signed count of unread bits in the current byte at +4 and the current byte at +5. When fewer bits are left the next byte is
// loaded and the rest is read recursively. The result is masked to the requested bits.
u32 BitStream_ReadBits(u8 *self, s32 bits) {
    s32 avail;
    u32 cur;
    u32 value;
    s32 need;
    u8 *cursor;

    avail = *(s8 *)(self + 4);
    cur = *(u8 *)(self + 5);
    if (avail < bits) {
        need = bits - avail;
        cursor = *(u8 **)self;
        *(u8 **)self = cursor + 1;
        *(u8 *)(self + 5) = *cursor;
        *(s8 *)(self + 4) = 8;
        value = BitStream_ReadBits(self, need) | (cur << need);
    } else {
        value = cur >> (avail - bits);
        *(s8 *)(self + 4) = (s8)(avail - bits);
    }
    return value & (0xff >> (8 - bits));
}
