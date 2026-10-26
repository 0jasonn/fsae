#include "engine/functions.h"
#include "global.h"

extern "C" s32 ResCursor_Seek(u8 *cursor, u32 index);
extern "C" s32 func_020c323c(u8 *cursor);
extern "C" void MIi_CpuCopy16(const void *src, void *dst, u32 size);

// ResCursor_SeekAndReset (ResCursor_SeekAndReset, provisional name): ResCursor_Seek, and on success clears the word at +0x10.
extern "C" s32 ResCursor_SeekAndReset(u8 *cursor, u32 index);
ARM s32 ResCursor_SeekAndReset(u8 *cursor, u32 index) {
    s32 found;

    found = ResCursor_Seek(cursor, index);
    if (found != 0) {
        *(u32 *)(cursor + 0x10) = 0;
    }
    return found;
}

// ResPlayer_Init (ResPlayer_Init, provisional name): clears the cursor at +0x20 and sets the fields of the player record.
extern "C" void ResCursor_Clear(u8 *cursor);
extern "C" void ResPlayer_Init(u8 *player);
ARM void ResPlayer_Init(u8 *player) {
    ResCursor_Clear(player + 0x20);
    *(u32 *)player = 0;
    *(u32 *)(player + 4) = 0;
    *(u32 *)(player + 8) = 0;
    *(u32 *)(player + 0xc) = 1;
    *(u32 *)(player + 0x10) = 0;
    *(u32 *)(player + 0x14) = 0x1000;
    *(u32 *)(player + 0x18) = 0;
    *(u32 *)(player + 0x1c) = 0;
}

// ResCursor_Clear (ResCursor_Clear, provisional name): zeroes the two positions, the entry and the halfword at +0xc.
extern "C" void ResCursor_Clear(u8 *cursor);
ARM void ResCursor_Clear(u8 *cursor) {
    *(u32 *)cursor = 0;
    *(u32 *)(cursor + 4) = 0;
    *(u32 *)(cursor + 8) = 0;
    *(u16 *)(cursor + 0xc) = 0;
}

