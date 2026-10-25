#include "engine/functions.h"
#include "global.h"
#include "types.h"

// rec_format_2: functions Rec_formatU32 (0x020b7268), Rec_formatHalfOrU32 (0x020b728c) and Rec_formatCond (0x020b72ec),
// matching. They follow Rec_setName (0x020b7248, rec_init.cpp) and call the two formatters of rec_format.cpp.
// The record layout (name at +4, output at +0x83, halfword at +0x102) is described in rec_format.cpp.

extern "C" s32 Rec_formatStrU32(void *dst, s32 size, const u8 *name, u32 value, s32 arg);
extern "C" s32 Rec_formatStrU32S16(void *dst, s32 size, const u8 *name, u32 value, u16 half, s32 arg);

// Rec_formatCond(rec, value, half, arg) (0x020b72ec, provisional name): formats the record as Rec_formatStrU32S16 when
// half is not zero and as Rec_formatStrU32 otherwise; returns whether the formatted length is not zero
extern "C" BOOL Rec_formatCond(void *self, u32 value, u16 half, s32 arg);
ARM BOOL Rec_formatCond(void *self, u32 value, u16 half, s32 arg) {
    s32 length;

    if (half != 0) {
        length = Rec_formatStrU32S16((u8 *)self + 0x83, 0x7f, (u8 *)self + 4, value, half, arg);
    } else {
        length = Rec_formatStrU32((u8 *)self + 0x83, 0x7f, (u8 *)self + 4, value, arg);
    }
    return length != 0;
}
