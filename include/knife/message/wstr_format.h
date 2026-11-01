#ifndef WIP_A_WSTR_FORMAT_H
#define WIP_A_WSTR_FORMAT_H

#include "global.h"
#include "types.h"

// Output buffer of halfwords filled by WstrBuf_Write (the wide counterpart of RingBuf).
typedef struct WstrBuf {
    u16 *buf;
    u32 size;
    u32 pos;
} WstrBuf;

extern "C" void *Mem_CopyHalfwords(void *dst, const void *src, u32 count);
extern "C" void *WstrBuf_Write(WstrBuf *wb, const void *src, u32 count);
extern "C" s32 func_02009980(void *(*writer)(WstrBuf *, const void *, u32), WstrBuf *ctx, const u16 *fmt, void *args);
extern "C" s32 Wstr_VSnprintf(u16 *dst, u32 size, const u16 *fmt, void *args);
extern "C" s32 Wstr_Snprintf(u16 *dst, u32 size, const u16 *fmt, ...);

#endif
