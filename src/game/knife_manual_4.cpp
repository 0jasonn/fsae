#include "engine/functions.h"
#include "global.h"
#include "game/knife_power.h"
#include "game/g_knife_manual.h"

// Functions in this file (original names from the debug build):
//   Knife::i_postprocManual (0x020c7e58)

namespace Knife {

// Knife::i_postprocManual() (0x020c7e58): frees the three blocks and the single block of the manual object, then
// restores the graphics settings, clears the object and unlocks the sleep state
ARM void i_postprocManual(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (data_0218704c.blocks[i] != 0) {
            i_deallocate(data_0218704c.blocks[i]);
            data_0218704c.blocks[i] = 0;
        }
    }
    if (data_0218704c.block14 != 0) {
        i_deallocate(data_0218704c.block14);
        data_0218704c.block14 = 0;
    }
    m4aEnterManualAlias();
    i_restoreGfxSettings();
    MI_CpuFill8(&data_0218704c, 0, 0x40);
    ((PowerManager *)Knife_GetPowerManager())->unlockSleep();
}

}
