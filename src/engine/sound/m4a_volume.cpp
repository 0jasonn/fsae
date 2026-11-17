#include "engine/functions.h"
#include "engine/sound/m4a.h"

// MPlayGetVolume (0x0208d830): the volume of a song. For the wave numbers (0x1ea to 0x1f3) it is the average of the two
// wave slots, otherwise the volume of the sequence handle (0 when the song is not playing).
u16 MPlayGetVolume(u16 songNum) {
    u16 volume = 0;
    s32 slot;
    void *handle;

    if (songNum >= 0x1ea && songNum < 0x1f4) {
        for (slot = 0; slot < 2; slot++) {
            volume = (u16)(volume + (u16)knifeSoundGetFlag0e(Knife_Sound_System_getWaveHandle(slot)));
        }
        volume = volume / 2;
    } else {
        handle = Knife_Sound_System_findHandle(songNum);
        if (handle != NULL) {
            volume = (u16)knifeSoundGetFlag0e(handle);
        }
    }
    return volume;
}
