#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/m4a.h"

// m4aSongNumStartOrContinue (0x0208d610): continues the song when it is already playing, otherwise starts it
extern "C" u32 m4aSongNumContinue(u32 songNum, u32 arg);
extern "C" u32 m4aSongNumIsPlaying(u16 songNum);
extern "C" u32 m4aSongNumStartOrContinue(u16 songNum);
ARM u32 m4aSongNumStartOrContinue(u16 songNum) {
    if (m4aSongNumIsPlaying(songNum) != 0) {
        return m4aSongNumContinue(songNum, 0);
    }
    return m4aSongNumStart(songNum);
}

// m4aSongNumSetVolume (0x0208d63c): sets the level of the song with the given number (both wave slots for numbers
// 0x1ea to 0x1f3, otherwise its handle). The level is scaled by 16 and kept to 16 bits.
extern "C" void m4aSongNumSetVolume(u16 songNum, u16 volume);
ARM void m4aSongNumSetVolume(u16 songNum, u16 volume) {
    u16 level;
    s32 i;
    void *handle;

    level = (u16)(volume << 4);
    if (songNum >= 0x1ea && songNum < 0x1f4) {
        for (i = 0; i < 2; i++) {
            Knife_Sound_Handle_stop(Knife_Sound_System_getWaveHandle(i), level, 1);
        }
        return;
    }
    handle = Knife_Sound_System_findHandle(songNum);
    if (handle == NULL) {
        return;
    }
    Knife_Sound_Handle_stop(handle, level, 1);
}
