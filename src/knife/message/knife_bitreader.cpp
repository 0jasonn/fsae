#include "engine/functions.h"
#include "global.h"
#include "knife/message/knife_canvas.h"

// NNSi_G2dBitReaderRead(NNSiG2dBitReader*, int) (0x0209ffec): reads bits most significant first
u32 NNSi_G2dBitReaderRead(NNSiG2dBitReader *reader, int bits) {
    int left = reader->bitsLeft;
    u32 cur = reader->bitBuf;
    u32 value;

    if (left < bits) {
        u8 *src = reader->ptr;
        int remain = bits - left;

        reader->ptr = src + 1;
        reader->bitBuf = *src;
        reader->bitsLeft = 8;
        value = NNSi_G2dBitReaderRead(reader, remain) | (cur << remain);
    } else {
        int rest = left - bits;

        value = cur >> rest;
        reader->bitsLeft = rest;
    }
    return value & (0xff >> (8 - bits));
}
