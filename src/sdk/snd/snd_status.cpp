#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/dc_cache.h"
#include "sdk/snd/snd_work.h"

// SND_GetPlayerStatus() (0x0201b79c): bit mask of the sequence players that are running, from the ARM7's shared block.
u32 SND_GetPlayerStatus(void) {
    DC_InvalidateRange(&data_0212b8e0->playerStatus, 4);
    return data_0212b8e0->playerStatus;
}

// SND_GetChannelStatus() (0x0201b7c4): bit mask of the busy hardware channels.
u16 SND_GetChannelStatus(void) {
    DC_InvalidateRange(&data_0212b8e0->channelStatus, 2);
    return data_0212b8e0->channelStatus;
}
