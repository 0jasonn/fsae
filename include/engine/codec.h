#ifndef WIP_A_CODEC_H
#define WIP_A_CODEC_H

#include "types.h"

// Character codec record. data_020df74c[2] points at the record in the ROM data (data_020df708): entry 0 converts
// one character to a wide character, entry 1 stores one byte through a pointer.
typedef s32 (*CodecConvertFn)(u16 *wide, const u8 *src, u32 count);
typedef s32 (*CodecStoreFn)(u8 *target, s32 value);

typedef struct CodecOps {
    CodecConvertFn convert;
    CodecStoreFn store;
    u32 unk_08;
    u32 unk_0c;
    u32 unk_10;
    void *unk_14;
} CodecOps;

extern CodecOps *data_020df74c[];

extern "C" s32 Codec_ConvertChar(u16 *wide, const u8 *src, u32 count);
extern "C" s32 Codec_StoreChar(u8 *target, s32 value);
extern "C" u32 Codec_WideToBytes(u8 *dst, const u16 *src, u32 max);
extern "C" s32 Codec_ByteToWide(u16 *wide, const u8 *src, u32 count);

#endif
