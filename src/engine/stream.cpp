#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" s32 func_02005798(u32 a, u32 b, u32 c, u32 d);
extern "C" void *CopyBytes(void *dst, const void *src, u32 count);

// Calls func_02005798 with (b, 1, c, a) and returns a when the result equals c, otherwise 0.
extern "C" s32 Sub_CallChecked(s32 a, s32 b, s32 c);

ARM s32 Sub_CallChecked(s32 a, s32 b, s32 c) {
    s32 result;

    result = func_02005798(b, 1, c, a);
    if (c != result) {
        a = 0;
    }
    return a;
}

// Writes count bytes of src into the buffer at buf + pos (count is cut to the space left below size) and advances pos.
typedef struct RingBuf {
    u8 *buf;
    u32 size;
    u32 pos;
} RingBuf;

extern "C" s32 RingBuf_Write(RingBuf *rb, const void *src, u32 count);

ARM s32 RingBuf_Write(RingBuf *rb, const void *src, u32 count) {
    u32 pos;

    pos = rb->pos;
    if (pos + count > rb->size) {
        count = rb->size - pos;
    }
    CopyBytes(rb->buf + pos, src, count);
    rb->pos += count;
    return 1;
}
