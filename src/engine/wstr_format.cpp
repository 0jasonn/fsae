#include "engine/functions.h"
#include "engine/wstr_format.h"
#include "global.h"
#include "types.h"

// WstrBuf_Write(wb, src, count) (0x0200a2e4): copies up to count halfwords from src to the buffer at its position, cut to
// the space left, and advances the position. Returns what Mem_CopyHalfwords returns.
ARM void *WstrBuf_Write(WstrBuf *wb, const void *src, u32 count) {
    u32 pos;
    void *result;

    pos = wb->pos;
    if (pos + count > wb->size) {
        count = wb->size - pos;
    }
    result = Mem_CopyHalfwords(wb->buf + pos, src, count);
    wb->pos += count;
    return result;
}

// Wstr_Snprintf(dst, size, fmt, ...) (0x0200a324): variadic wrapper of Wstr_VSnprintf. The variadic arguments follow fmt
// in the caller's stack words, so args starts at the word after fmt.
ARM s32 Wstr_Snprintf(u16 *dst, u32 size, const u16 *fmt, ...) {
    return Wstr_VSnprintf(dst, size, fmt, (u8 *)(((u32)&fmt) & ~3) + 4);
}

// Wstr_VSnprintf(dst, size, fmt, args) (0x0200a34c): formats fmt with args into dst (halfwords) through WstrBuf_Write.
// Returns the length when the text fits, -1 when it was cut, and a negative formatter result unchanged.
typedef struct WstrFormatCtx {
    u32 unk_00;
    WstrBuf buf;
} WstrFormatCtx;

ARM s32 Wstr_VSnprintf(u16 *dst, u32 size, const u16 *fmt, void *args) {
    WstrFormatCtx ctx;
    s32 length;

    ctx.buf.buf = dst;
    ctx.buf.size = size;
    ctx.buf.pos = 0;
    ctx.unk_00 = 0;
    length = func_02009980(WstrBuf_Write, &ctx.buf, fmt, args);
    if (length < 0) {
        return length;
    }
    if ((u32)length < size) {
        dst[length] = 0;
        return length;
    }
    dst[size - 1] = 0;
    return -1;
}
