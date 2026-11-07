#include "engine/functions.h"
#include "engine/sound/sndstate_entries_api.h"

extern "C" BOOL SSP_GetDateTime(u32 id, u32 value);

// SSP_GetDateTime (0x020c0c28): TRUE when running the sound state entries for the id and value reports 0
BOOL SSP_GetDateTime(u32 id, u32 value) {
    return SndState_RunEntries(id, value) == 0;
}
