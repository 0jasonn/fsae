#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" void *CopyBytes(void *dst, const void *src, u32 count);
extern "C" void *Mem_CopyHalfwords(void *dst, const void *src, u32 count);
extern "C" u16 *Mem_FindHalfword(const u16 *buf, s32 value, u32 count);

// Copies count halfwords (count * 2 bytes) through CopyBytes.
ARM void *Mem_CopyHalfwords(void *dst, const void *src, u32 count) {
    return CopyBytes(dst, src, count * 2);
}

// Returns the first halfword in buf equal to value within count halfwords, or NULL.
ARM u16 *Mem_FindHalfword(const u16 *buf, s32 value, u32 count) {
    while (count != 0) {
        if (*buf == value) {
            return (u16 *)buf;
        }
        buf++;
        count--;
    }
    return NULL;
}
