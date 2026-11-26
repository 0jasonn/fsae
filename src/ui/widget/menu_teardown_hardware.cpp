#include "engine/functions.h"
#include "engine/fs_dirfile_api.h"
#include "engine/sound/sndsys_api.h"
#include "ui/widget/menu_teardown_hardware.h"
#include "ui/widget/menu.h"
#include "sdk/gx/gx.h"

// Stops touch sampling and audio, turns the display off, then releases any menu-owned
// resources. The flags are confirmed at menu offsets 0x40622..0x40624.
extern "C" void Menu_teardownHardware(MenuWork *menu) {
    s32 dma = 4;

    TP_RequestAutoSamplingStopAsync();
    TP_WaitBusy(dma);
    TP_CheckError(dma);
    SndSys_StopAll();
    GX_DispOff();
    *(volatile u32 *)0x04001000 &= ~0x00010000;
    if (menu->sub.flag622 != 0) {
        GX_SetDefaultDMA(-1);
    }
    func_02012c40();
    if (menu->sub.flag623 != 0) {
        GX_VBlankIntr(1);
    }
    if (menu->sub.flag624 == 0) {
        func_0218a860(0);
    }
    if (*((u8 *)menu + 0x80) != 0) {
        Fs_ReleaseArchive((u8 *)menu + 0x18);
    }
    if (*((u8 *)menu + 0xec) != 0) {
        Fs_ReleaseArchive((u8 *)menu + 0x84);
    }
}
