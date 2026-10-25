#include "engine/functions.h"
#include "global.h"
#include "types.h"

// rec_format_2: functions Rec_formatU32 (0x020b7268), Rec_formatHalfOrU32 (0x020b728c) and Rec_formatCond (0x020b72ec),
// matching. They follow Rec_setName (0x020b7248, rec_init.cpp) and call the two formatters of rec_format.cpp.
// The record layout (name at +4, output at +0x83, halfword at +0x102) is described in rec_format.cpp.

extern "C" s32 Rec_formatStrU32(void *dst, s32 size, const u8 *name, u32 value, s32 arg);
extern "C" s32 Rec_formatStrU32S16(void *dst, s32 size, const u8 *name, u32 value, u16 half, s32 arg);

// Rec_formatU32(rec, value, arg) (0x020b7268, provisional name): Rec_formatStrU32 on the record
extern "C" s32 Rec_formatU32(void *self, u32 value, s32 arg);
ARM s32 Rec_formatU32(void *self, u32 value, s32 arg) {
    return Rec_formatStrU32((u8 *)self + 0x83, 0x7f, (u8 *)self + 4, value, arg);
}

// Rec_formatHalfOrU32(rec, value, arg) (0x020b728c, provisional name): Rec_formatStrU32S16 when the halfword at +0x102 is
// not zero, Rec_formatStrU32 otherwise
extern "C" s32 Rec_formatHalfOrU32(void *self, u32 value, s32 arg);
ARM s32 Rec_formatHalfOrU32(void *self, u32 value, s32 arg) {
    u16 half;

    half = *(u16 *)((u8 *)self + 0x102);
    if (half != 0) {
        return Rec_formatStrU32S16((u8 *)self + 0x83, 0x7f, (u8 *)self + 4, value, half, arg);
    }
    return Rec_formatStrU32((u8 *)self + 0x83, 0x7f, (u8 *)self + 4, value, arg);
}
