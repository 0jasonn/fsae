#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"
#include "game/menu_wip.h"

// Functions in this file (provisional name):
//   SndMaster_SetPan (SndMaster_SetPan)

extern "C" {
void SND_SetMasterPan(u32 pan);
void SND_ResetMasterPan(void);
}

// SndMaster_SetPan (0x020bf23c): sets the master pan to the centre when the flag is set, otherwise resets it.
extern "C" void SndMaster_SetPan(s32 enable);
ARM void SndMaster_SetPan(s32 enable) {
    if (enable != 0) {
        SND_SetMasterPan(0x40);
    } else {
        SND_ResetMasterPan();
    }
}
