#include "engine/functions.h"
#include "global.h"

// TWL boot code, 0x020828b8 to 0x020829d8.
//   BeforeTask (0x020828b8): moves the pending flag of frameCounter into its second byte and clears the first.
//   twlInitVRAM (0x020828d4): clears the VRAM and palette areas.
//   twlInitAgb (0x0208294c): sets the graphics mode and the display control bit.
//   twlInitSubDisplay (0x02082994): sets up the sub display and the KnifeApp settings block.

extern u8 frameCounter[];
extern "C" void func_0201500c(u32 a);
extern "C" void Vram_DisableBankTail(void);
extern "C" void func_020148f0(u32 a);
extern "C" void func_02014af4(u32 a);
extern "C" void Vram_SetBankGroupA(u32 a);
extern "C" void func_02015120(u32 a);
extern "C" void Knife_Comm_WirelessIcon_initialize_16x16_ColorMode(void *self, u32 a, u32 b);
extern "C" void GX_SetGraphicsMode(u32 a, u32 b, u32 c);

// BeforeTask (0x020828b8)
ARM void BeforeTask(void) {
    frameCounter[0x14] = frameCounter[0x13];
    frameCounter[0x13] = 0;
}

// twlInitVRAM (0x020828d4)
ARM void twlInitVRAM(void) {
    func_0201500c(0x1ff);
    MIi_CpuClearFast(0, (void *)0x6800000, 0xa4000);
    Vram_DisableBankTail();
    MIi_CpuClearFast(0xc0, (void *)0x7000000, 0x400);
    MIi_CpuClearFast(0, (void *)0x5000000, 0x400);
    MIi_CpuClearFast(0xc0, (void *)0x7000400, 0x400);
    MIi_CpuClearFast(0, (void *)0x5000400, 0x400);
}

// twlInitAgb (0x0208294c)
ARM void twlInitAgb(void) {
    u32 control;

    func_020148f0(1);
    func_02014af4(2);
    GX_SetGraphicsMode(1, 0, 0);
    control = *(volatile u32 *)0x4000000;
    *(volatile u32 *)0x4000000 = (control & 0xffcfffef) | 0x10;
}

// twlInitSubDisplay (0x02082994)
ARM void twlInitSubDisplay(void) {
    u8 *app;

    Vram_SetBankGroupA(4);
    func_02015120(8);
    app = (u8 *)KnifeApp_getInstance();
    Knife_Comm_WirelessIcon_initialize_16x16_ColorMode(app + 4, 1, 0xf);
    app[0x18] = 1;
    *(u32 *)(app + 0x10) = 0;
    *(u32 *)(app + 0x14) = 0;
}
