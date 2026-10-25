#include "engine/functions.h"
#include "global.h"
#include "types.h"

// rec_format: functions Rec_formatStrU32 (0x020b7154) and Rec_formatStrU32S16 (0x020b71ac), matching. The formatters of the record class of rec_init.cpp. The name is the string at +4, the output buffer is
// the 0x7f bytes at +0x83, and the halfword at +0x102 selects the variant that also prints a packed halfword.
// data_02126bf0 and data_02126bfc are the format strings. func_0201dc94 is a printf wrapper and func_020c2b38 returns
// the length of the formatted string.

extern u8 data_02126bf0[];
extern u8 data_02126bfc[];

extern "C" void Packed_setU32BE(void *self, u32 value);
extern "C" void Packed_setS16(void *self, s32 value);
extern "C" s32 func_0201dc94(void *dst, s32 size, const u8 *format, ...);
extern "C" s32 func_020c2b38(void *dst);

// Rec_formatStrU32(dst, size, name, value, arg) (0x020b7154, provisional name): formats dst from data_02126bf0 with the
// name, the packed value and arg, and returns the length of the result
extern "C" s32 Rec_formatStrU32(void *dst, s32 size, const u8 *name, u32 value, s32 arg);
ARM s32 Rec_formatStrU32(void *dst, s32 size, const u8 *name, u32 value, s32 arg) {
    u8 packed[5];

    Packed_setU32BE(packed, value);
    func_0201dc94(dst, size, data_02126bf0, name, packed, arg);
    return func_020c2b38(dst);
}

// Rec_formatStrU32S16(dst, size, name, value, half, arg) (0x020b71ac, provisional name): as Rec_formatStrU32, with the
// value also packed as a halfword and formatted from data_02126bfc
extern "C" s32 Rec_formatStrU32S16(void *dst, s32 size, const u8 *name, u32 value, u16 half, s32 arg);
ARM s32 Rec_formatStrU32S16(void *dst, s32 size, const u8 *name, u32 value, u16 half, s32 arg) {
    u8 packed[5];
    u8 packedHalf[3];

    Packed_setU32BE(packed, value);
    Packed_setS16(packedHalf, half);
    func_0201dc94(dst, size, data_02126bfc, name, packed, packedHalf, arg);
    return func_020c2b38(dst);
}
