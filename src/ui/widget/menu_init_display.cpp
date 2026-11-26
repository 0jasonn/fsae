#include "engine/gx_misc_api.h"
#include "sdk/gx/vram_bank_bits_api.h"
#include "engine/functions.h"
#include "sdk/gx/vram_group.h"
#include "ui/widget/ctrl_wrap_api.h"
#include "sdk/gx/gx.h"

#define REG16(addr) (*(volatile u16 *)(addr))
#define REG32(addr) (*(volatile u32 *)(addr))

extern "C" {
void func_02014d1c(s32 banks);
void func_020bdb34(void);
}

extern "C" void func_020bdb34(void) {
    REG16(0x04000304) = REG16(0x04000304) & ~0x8000;
    GX_SetGraphicsMode(1, 3, 0);
    GXS_SetGraphicsMode(3);
    func_020148f0(3);
    REG32(0x04000000) = (REG32(0x04000000) & ~0x38000000) | 0x10000000;
    REG32(0x04000000) = (REG32(0x04000000) & ~0x07000000) | 0x03000000;
    REG16(0x04000008) = (u16)(REG16(0x04000008) & ~3);
    REG16(0x04000008) = (u16)(REG16(0x04000008) & (u16)~0x40);
    REG16(0x04000008) = (u16)((REG16(0x04000008) & 0x43) | 0xc000);
    REG16(0x0400000a) = (u16)((REG16(0x0400000a) & ~3) | 1);
    REG16(0x0400000a) = (u16)(REG16(0x0400000a) & (u16)~0x40);
    REG16(0x0400000a) = (u16)((REG16(0x0400000a) & 0x43) | 0xc400);
    REG16(0x0400000c) = (u16)((REG16(0x0400000c) & ~3) | 2);
    REG16(0x0400000c) = (u16)(REG16(0x0400000c) & (u16)~0x40);
    REG16(0x0400000c) = (u16)((REG16(0x0400000c) & 0x43) | 0x8800);
    REG16(0x0400000e) = (u16)((REG16(0x0400000e) & ~3) | 3);
    REG16(0x0400000e) = (u16)(REG16(0x0400000e) & (u16)~0x40);
    REG16(0x0400000e) = (u16)((REG16(0x0400000e) & 0x43) | 0x6000 | 0x84);
    Vram_SetBankGroupA(4);

    REG16(0x0400100e) = (u16)((REG16(0x0400100e) & ~3) | 0);
    REG16(0x0400100e) = (u16)(REG16(0x0400100e) & (u16)~0x40);
    REG16(0x0400100e) = (u16)((REG16(0x0400100e) & 0x43) | 0x6000 | 0x84);
    func_02014af4(0x10);
    REG32(0x04000000) = (REG32(0x04000000) & 0xffcfffef) | Ctrl_getConst();
    func_02014d1c(0x20);
    func_02015120(8);
    REG32(0x04001000) = (REG32(0x04001000) & 0xffcfffef) | Ctrl_getConst();
    Vram_SetBankGroupC(0x100);
    REG32(0x04000000) = (REG32(0x04000000) & ~0x1f00) | 0x1800;
    REG32(0x04001000) = (REG32(0x04001000) & ~0x1f00) | 0x1800;
    GXx_SetMasterBrightness_((void *)0x0400006c, 0x10);
    GXx_SetMasterBrightness_((void *)0x0400106c, 0x10);
    Gx_setBlendAlpha();
    REG16(0x04000048) = (u16)((REG16(0x04000048) & ~0x3f) | 0x28);
    REG16(0x0400004a) = (u16)((REG16(0x0400004a) & ~0x3f) | 0x37);
    REG16(0x04001048) = (u16)((REG16(0x04001048) & ~0x3f) | 0x28);
    REG16(0x0400104a) = (u16)((REG16(0x0400104a) & ~0x3f) | 0x37);
}
