#include "engine/functions.h"
#include "global.h"
#include "knife/app/twl.h"
#include "sdk/gx/vram_group.h"

// TWL boot code, 0x020828b8 to 0x020829d8.
//   BeforeTask (0x020828b8): moves the pending flag of frameCounter into its second byte and clears the first.
//   twlInitVRAM (0x020828d4): clears the VRAM and palette areas.
//   twlInitAgb (0x0208294c): sets the graphics mode and the display control bit.
//   twlInitSubDisplay (0x02082994): sets up the sub display and the KnifeApp settings block.

#include "engine/frame_counter.h"
extern "C" void Vram_SetLcdcBits(u32 a);
extern "C" void Vram_DisableBankTail(void);
extern "C" void Knife_Comm_WirelessIcon_initialize_16x16_ColorMode(void *self, u32 a, u32 b);

// BeforeTask (0x020828b8)
void BeforeTask(void) {
    frameCounter.playersBoundPrev = frameCounter.playersBound;
    frameCounter.playersBound = 0;
}

// twlInitVRAM (0x020828d4)
void twlInitVRAM(void) {
    Vram_SetLcdcBits(0x1ff);
    MIi_CpuClearFast(0, (void *)0x6800000, 0xa4000);
    Vram_DisableBankTail();
    MIi_CpuClearFast(0xc0, (void *)0x7000000, 0x400);
    MIi_CpuClearFast(0, (void *)0x5000000, 0x400);
    MIi_CpuClearFast(0xc0, (void *)0x7000400, 0x400);
    MIi_CpuClearFast(0, (void *)0x5000400, 0x400);
}

// twlInitAgb (0x0208294c)
void twlInitAgb(void) {
    u32 control;

    GX_SetBankForBG(1);
    GX_SetBankForOBJ(2);
    GX_SetGraphicsMode(1, 0, 0);
    control = *(volatile u32 *)0x4000000;
    *(volatile u32 *)0x4000000 = (control & 0xffcfffef) | 0x10;
}

// twlInitSubDisplay (0x02082994)
void twlInitSubDisplay(void) {
    u8 *app;

    Vram_SetBankGroupA(4);
    GX_SetBankForSubOBJ(8);
    app = (u8 *)KnifeApp_getInstance();
    Knife_Comm_WirelessIcon_initialize_16x16_ColorMode(app + 4, 1, 0xf);
    app[0x18] = 1;
    *(u32 *)(app + 0x10) = 0;
    *(u32 *)(app + 0x14) = 0;
}
