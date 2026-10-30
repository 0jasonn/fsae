#include "engine/functions.h"
#include "global.h"

extern "C" void BgExtPalette_Load(s32 screen, u8 *palette, u8 *table);
extern "C" void BgPalette_Load(s32 screen, u8 *palette, u8 *table);
extern "C" const u16 data_020df07c[];

// BgExtPalette_ResolveSlot (provisional name): the index of the value in data_020df07c; when that register offset is zero
// the index is returned, otherwise index + 2 when bit 0x2000 of the halfword at the register is set.
extern "C" u32 BgExtPalette_ResolveSlot(u32 index);
ARM u32 BgExtPalette_ResolveSlot(u32 index) {
    u16 value;

    value = data_020df07c[index];
    if (value == 0) {
        return index;
    }
    if ((*(u16 *)((u32)value + 0x4000000) & 0x2000) != 0) {
        index += 2;
    }
    return index;
}

// BgPalette_LoadSelect (provisional name): when useExt is set, the slot is resolved and the extended BG palette loads, otherwise
// the plain BG palette loads.
extern "C" void BgPalette_LoadSelect(s32 screen, u32 useExt, u8 *palette, u8 *table);
ARM void BgPalette_LoadSelect(s32 screen, u32 useExt, u8 *palette, u8 *table) {
    if (useExt != 0) {
        BgExtPalette_Load((s32)BgExtPalette_ResolveSlot(screen), palette, table);
    } else {
        BgPalette_Load(screen, palette, table);
    }
}

