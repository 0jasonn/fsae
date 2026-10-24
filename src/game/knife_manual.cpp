#include "engine/functions.h"
#include "global.h"
#include "game/g_knife_manual.h"

// Functions in this file (original names from the debug build):
//   Knife::runManual (0x020c7c10), Knife_GetManualFlag (0x020c7c3c, provisional name)

extern "C" void Knife_RunMenuWrapper(void);
extern "C" void Knife_ForwardMenuWrapper(void);

namespace Knife {

// Knife::runManual() (0x020c7c10): runs the manual mode. Returns 0 when the preprocessing fails.
ARM s32 runManual(void) {
    if (i_preprocManual() == 0) {
        return 0;
    }
    i_initM2dLibrary();
    Knife_RunMenuWrapper();
    Knife_ForwardMenuWrapper();
    i_postprocManual();
    return 1;
}

}

// Knife_GetManualFlag (0x020c7c3c): the flag byte at +0x3c of the manual object
ARM u8 Knife_GetManualFlag(void) {
    return data_0218704c.flag3c;
}
