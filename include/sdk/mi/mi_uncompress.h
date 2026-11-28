#ifndef SDK_MI_MI_UNCOMPRESS_H
#define SDK_MI_MI_UNCOMPRESS_H

#include "engine/entity.h"

extern "C" {
void MI_UncompressLZ16(const void *src, void *dst);
// Checks the footer of a backward-compressed (BLZ) image of size bytes and decompresses it in place when the result
// fits in limit bytes: 0, -1 for a bad footer, -4 when too large.
s32 MI_SecureUncompressBLZ(u8 *data, u32 size, u32 limit);
void MI_UncompressBackward(void *bottom); // expands the BLZ data that ends at bottom (hand-written ARM)
}

#endif
