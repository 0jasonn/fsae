#ifndef SDK_MI_MI_MEMORY_H
#define SDK_MI_MI_MEMORY_H

// TwlSDK MI CPU memory fill and copy (hand-written ARM). The 16/32 variants need aligned buffers and sizes.
#include "types.h"

extern "C" {
void MIi_CpuClear16(u16 data, void *dest, u32 size);
void MIi_CpuCopy16(const void *src, void *dest, u32 size);
void OSi_CpuClear32(u32 data, void *dest, u32 size); // MIi_CpuClear32
void MIi_CpuCopy32(const void *src, void *dest, u32 size);
void MIi_CpuClearFast(u32 data, void *dest, u32 size);
void MIi_CpuCopyFast(const void *src, void *dest, u32 size);
void MI_CpuFill8(void *dest, u8 data, u32 size);
void MI_CpuFill(void *dest, u32 data, u32 size);
void MI_CpuCopy8(const void *src, void *dest, u32 size);
void MI_CpuCopy(const void *src, void *dest, u32 size);  // 0x02015e3c-0x0201612c (symbols.txt says size 0xa4, real size 0x2f0)
void MI_CpuMove(const void *src, void *dest, u32 size);  // 0x0201612c-0x02016440 (symbols.txt says size 0xbc, real size 0x314); overlap safe
}

#endif
