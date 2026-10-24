#ifndef WIP_A_KNIFE_COMM_ICON_H
#define WIP_A_KNIFE_COMM_ICON_H

#include "engine/functions.h"

// Knife::Comm::WirelessIcon (0x0209a660 to 0x0209a7c0). Field names are provisional.
typedef struct WirelessIcon {
    u8 unk_00[4];
    u8 enabled;      // 0x04: set by initialize, cleared by finalize
    u8 unk_05;       // 0x05
    u8 unk_06;       // 0x06
    u8 unk_07;
    s32 paletteNo;   // 0x08: the int argument of initialize (palette number)
    s32 unk_0c;      // 0x0c
    s32 charNo;      // 0x10
    u8 unk_14;       // 0x14
    u8 unk_15[3];
    u32 colorType;   // 0x18: ColorType argument of initialize, indexes a 16-byte table per type
} WirelessIcon;

// Knife::Comm::ChildInfo (0x0209a818 to 0x0209a890). Field names are provisional.
typedef struct ChildInfo {
    u8 unk_00[4];
    u8 flag04;       // 0x04: cleared by setup, set by cleanup
    u8 bytes05[6];   // 0x05: copied from the first source
    u8 unk_0b;
    u16 id;          // 0x0c
    u8 bytes0e[0x18]; // 0x0e: copied from the second source
} ChildInfo;

extern "C" void MI_CpuFill8(void *dst, u8 value, u32 size);
extern "C" void MI_CpuCopy8(const void *src, void *dst, u32 size);

#endif
