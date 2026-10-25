#ifndef WIP_A_STR_FORMAT_H
#define WIP_A_STR_FORMAT_H

#include "global.h"
#include "types.h"

// Output buffer filled by RingBuf_Write (same layout as the RingBuf in src/engine/stream.cpp).
typedef struct RingBuf {
    u8 *buf;
    u32 size;
    u32 pos;
} RingBuf;

extern "C" s32 RingBuf_Write(RingBuf *rb, const void *src, u32 count);
extern "C" s32 func_02007638(s32 (*writer)(RingBuf *, const void *, u32), RingBuf *ctx, const u8 *fmt, void *args);
extern "C" s32 Str_VSnprintf(u8 *dst, u32 size, const u8 *fmt, void *args);
extern "C" s32 Str_Sprintf(u8 *dst, const u8 *fmt, ...);

#endif
