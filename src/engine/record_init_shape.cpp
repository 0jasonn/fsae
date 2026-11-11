#include "engine/functions.h"
#include "engine/record_init.h"

static inline u32 CountLeadingZeros(u32 value) {
    asm { clz value, value }
    return value;
}

// Record_InitShape (0x020c5f48): Record_Init with the shape and size bits of the record looked up from the log2 of the
// width and height (each clamped to 3)
void Record_InitShape(u8 *self, u32 a, u32 width, u32 height, u32 d) {
    s32 widthLog;
    s32 heightLog;
    RecordShapeBits bits;

    if ((s32)width >= 8) {
        widthLog = 3;
    } else {
        widthLog = 31 - CountLeadingZeros(width);
    }
    if ((s32)height >= 8) {
        heightLog = 3;
    } else {
        heightLog = 31 - CountLeadingZeros(height);
    }
    const RecordShapeEntry *entry = &data_020df144.entry[heightLog][widthLog];
    bits.shape = entry->shape;
    bits.size = entry->size;
    Record_Init(self, a, width, height, d, (u32)data_020df138, *(u32 *)&bits);
}
