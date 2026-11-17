#include "engine/functions.h"
#include "global.h"
#include "engine/res_cursor_api.h"

// Reset both cursor positions before updating the active entry.
s32 ResCursor_InitRange(u8 *cursor) {
    s32 forward = *(s32 *)(cursor + 0x14) > 0;

    if (forward ^ *(s32 *)(cursor + 8)) {
        u8 *table = *(u8 **)(cursor + 0x1c);
        *(u32 *)cursor = *(u32 *)(table + 0xc) + (*(u16 *)(table + 2) << 3);
    } else {
        u8 *table = *(u8 **)(cursor + 0x1c);
        *(u32 *)cursor = *(u32 *)(table + 0xc) + (*(u16 *)table << 3) - 8;
    }
    *(u32 *)(cursor + 4) = *(u32 *)cursor;
    *(u32 *)(cursor + 0x10) = 0;
    return func_020c323c(cursor);
}

// ResCursor_SetTableAndInit (ResCursor_SetTableAndInit, provisional name): stores the table at +0x1c and runs ResCursor_InitRange.
s32 ResCursor_SetTableAndInit(u8 *cursor, u8 *table) {
    *(u8 **)(cursor + 0x1c) = table;
    return ResCursor_InitRange(cursor);
}

// VramObj_Copy16Offset (VramObj_Copy16Offset, provisional name): copies to the object VRAM at offset 0x400.
void VramObj_Copy16Offset(const void *src, u32 dst, u32 size) {
    MIi_CpuCopy16(src, (void *)(dst + 0x400 + 0x7000000), size);
}

// VramObj_Copy16 (VramObj_Copy16, provisional name): copies to the object VRAM at dst.
void VramObj_Copy16(const void *src, u32 dst, u32 size) {
    MIi_CpuCopy16(src, (void *)(dst + 0x7000000), size);
}
