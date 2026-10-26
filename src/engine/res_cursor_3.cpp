#include "engine/functions.h"
#include "global.h"

extern "C" s32 ResCursor_InitRange(u8 *cursor);
extern "C" void MIi_CpuCopy16(const void *src, void *dst, u32 size);

// ResCursor_SetTableAndInit (ResCursor_SetTableAndInit, provisional name): stores the table at +0x1c and runs ResCursor_InitRange.
extern "C" s32 ResCursor_SetTableAndInit(u8 *cursor, u8 *table);
ARM s32 ResCursor_SetTableAndInit(u8 *cursor, u8 *table) {
    *(u8 **)(cursor + 0x1c) = table;
    return ResCursor_InitRange(cursor);
}

// VramObj_Copy16Offset (VramObj_Copy16Offset, provisional name): copies to the object VRAM at offset 0x400.
extern "C" void VramObj_Copy16Offset(const void *src, u32 dst, u32 size);
ARM void VramObj_Copy16Offset(const void *src, u32 dst, u32 size) {
    MIi_CpuCopy16(src, (void *)(dst + 0x400 + 0x7000000), size);
}

// VramObj_Copy16 (VramObj_Copy16, provisional name): copies to the object VRAM at dst.
extern "C" void VramObj_Copy16(const void *src, u32 dst, u32 size);
ARM void VramObj_Copy16(const void *src, u32 dst, u32 size) {
    MIi_CpuCopy16(src, (void *)(dst + 0x7000000), size);
}
