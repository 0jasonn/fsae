#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Context of the ROM command: the offset at +8 and the second value at +0x30 are passed to FSi_IsUnreadableRomOffset.
typedef struct FsRomCmdCtx {
    u8 unk_00[8];
    u32 offset;              // 0x08
    u8 unk_0c[0x24];
    u32 romOffset;           // 0x30
} FsRomCmdCtx;

// Shared word with the ROM bank value at +4, passed (as u16) to the CARD and G3C lock calls.
typedef struct FsRomCmdState {
    u8 unk_00[4];
    u32 value;               // 0x04
} FsRomCmdState;

extern FsRomCmdState data_021297b8;

extern "C" s32 FSi_IsUnreadableRomOffset(u32 offset, u32 romOffset);
extern "C" void CARD_LockRom(u16 value);
extern "C" void G3C_Direct1(u16 value);

// FsRom_Command(ctx, cmd) (0x02012810): cmd 1 gives 4; cmd 7 gives 9 for an unreadable offset and 0x101 otherwise;
// cmd 9 and 10 lock the ROM or switch to direct mode with the value and give 0. Other values give 0x102.
extern "C" s32 FsRom_Command(FsRomCmdCtx *ctx, s32 cmd);

ARM s32 FsRom_Command(FsRomCmdCtx *ctx, s32 cmd) {
    switch (cmd) {
    case 9:
        CARD_LockRom((u16)data_021297b8.value);
        return 0;
    case 10:
        G3C_Direct1((u16)data_021297b8.value);
        return 0;
    case 7:
        if (FSi_IsUnreadableRomOffset(ctx->offset, ctx->romOffset) != 0) {
            return 9;
        }
        return 0x101;
    case 1:
        return 4;
    default:
        return 0x102;
    }
}
