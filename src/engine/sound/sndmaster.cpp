#include "engine/functions.h"
#include "sdk/snd/snd_command.h"
#include "global.h"
#include "ui/widget/menu.h"

// Functions in this file (provisional name):
//   SndMaster_SetPan (SndMaster_SetPan)

extern "C" {
}

// SndMaster_SetPan (0x020bf23c): sets the master pan to the centre when the flag is set, otherwise resets it.
extern "C" void SndMaster_SetPan(s32 enable);
void SndMaster_SetPan(s32 enable) {
    if (enable != 0) {
        SND_SetMasterPan(0x40);
    } else {
        SND_ResetMasterPan();
    }
}
