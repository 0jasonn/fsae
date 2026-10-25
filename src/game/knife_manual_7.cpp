#include "engine/functions.h"
#include "global.h"
#include "game/g_knife_manual.h"
#include "game/decls_g.h"

// Functions in this file (original names from the debug build):
//   Knife::i_restoreGfxSettings (0x020c7ed4)

namespace Knife {

// Knife::i_restoreGfxSettings() (0x020c7ed4): resets the display and the VRAM banks, sets up the touch panel, the
// wireless icon and the task state, and clears the menu state bytes of the application object
ARM void i_restoreGfxSettings(void) {
    u8 *app;

    func_02012c40();
    GX_DispOff();
    *(u32 *)0x04001000 = *(u32 *)0x04001000 & ~0x10000;
    func_0201500c(0x1ff);
    MIi_CpuClearFast(0, (void *)0x06800000, 0xa4000);
    Vram_DisableBankTail();
    MIi_CpuClearFast(0xc0, (void *)0x07000000, 0x400);
    MIi_CpuClearFast(0, (void *)0x05000000, 0x400);
    MIi_CpuClearFast(0xc0, (void *)0x07000400, 0x400);
    MIi_CpuClearFast(0, (void *)0x05000400, 0x400);
    func_020148f0(1);
    func_02014af4(2);
    GX_SetGraphicsMode(1, 0, 0);
    *(u32 *)0x04000000 = (*(u32 *)0x04000000 & 0xffcfffef) | 0x10;
    func_02015084(4);
    func_02015120(8);
    TP_Init();
    if (TP_GetUserInfo(data_0212c57c) == 0) {
        OS_Terminate();
    }
    TP_SetCalibrateParam(data_0212c57c);
    app = (u8 *)KnifeApp_getInstance();
    Knife_Comm_WirelessIcon_initialize_16x16_ColorMode(app + 4, 1, 0xf);
    app[0x18] = 1;
    *(u32 *)(app + 0x10) = 0;
    *(u32 *)(app + 0x14) = 0;
    Irq_InitVBlank();
    data_0212c524 = 0;
    DispReset();
    *(u16 *)0x05000000 = 0x6739;
    data_021355a0 = 0x6739;
    ObjWorkPoolClear();
    ObjMoveInit();
    MessageInitialize();
    TelopInitialize();
    ComInitState();
    Task_Chain(7);
    subTask_game_start_reload();
    func_020827a8(3);
    data_0212c4dc = 1;
}

}
