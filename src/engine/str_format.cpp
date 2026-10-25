#include "engine/functions.h"
#include "engine/str_format.h"
#include "global.h"
#include "types.h"

// Output context for func_02007638: a leading word, then the RingBuf that RingBuf_Write fills.
typedef struct StrFormatCtx {
    u32 unk_00;
    RingBuf buf;
} StrFormatCtx;

// Str_VSnprintf(dst, size, fmt, args) (0x02008080): formats fmt with args into dst through RingBuf_Write, which keeps at
// most size bytes. Returns the formatted length. A NUL is written after the text, or over the last byte if it did not fit.
ARM s32 Str_VSnprintf(u8 *dst, u32 size, const u8 *fmt, void *args) {
    StrFormatCtx ctx;
    s32 length;

    ctx.buf.buf = dst;
    ctx.buf.size = size;
    ctx.buf.pos = 0;
    ctx.unk_00 = 0;
    length = func_02007638(RingBuf_Write, &ctx.buf, fmt, args);
    if (dst == NULL) {
        return length;
    }
    if ((u32)length < size) {
        dst[length] = 0;
        return length;
    }
    if (size != 0) {
        dst[size - 1] = 0;
    }
    return length;
}

// Str_Sprintf(dst, fmt, ...) (0x020080e4): sprintf without a size limit. The variadic arguments are the caller's
// stack words after fmt, so args starts at the word after fmt.
ARM s32 Str_Sprintf(u8 *dst, const u8 *fmt, ...) {
    return Str_VSnprintf(dst, (u32)-1, fmt, (u8 *)(((u32)&fmt) & ~3) + 4);
}
