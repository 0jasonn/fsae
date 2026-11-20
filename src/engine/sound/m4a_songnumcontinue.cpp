#include "engine/functions.h"
#include "global.h"
#include "types.h"
#define m4aSongNumContinue m4aSongNumContinue_header_decl
#include "engine/sound/m4a.h"
#undef m4aSongNumContinue

// m4aSongNumContinue (0x0208d6a8): resumes the song with the given number at the given level (the low 12 bits of arg,
// scaled by 16): both wave slots for numbers 0x1ea to 0x1f3, otherwise the sequence handle. Starts the song when it is
// not playing. m4a.h declares it with a u32 first parameter; the ROM takes the u16 the callers pass (proposed: u16).

extern "C" u32 m4aSongNumContinue(u16 songNum, u32 arg);
u32 m4aSongNumContinue(u16 songNum, u32 arg) {
    s32 i;
    void *handle;
    u16 slot;
    s32 level;
    KnifeSoundWaveHandle *wave;
    s32 notPlaying;
    s32 waveIndex;

    level = (arg & 0xfff) << 4;
    if (songNum >= 0x1ea && songNum < 0x1f4) {
        waveIndex = songNum - 0x1ea;
        notPlaying = 1;
        for (i = 0; i < 2; i++) {
            slot = i + waveIndex * 2;
            wave = Knife_Sound_System_getWaveHandle(i);
            if (songNum == *(s32 *)((u8 *)wave + 4)) {
                Knife_Sound_Handle_volume(wave, ((M4aRecord *)((M4aSoundTable *)&data_02176238)->records)[slot].field10, level);
                Knife_Sound_Handle_pause(wave, 0);
                notPlaying = 0;
            }
        }
        if (notPlaying) {
            m4aSongNumStart(songNum);
        }
    } else {
        handle = Knife_Sound_System_findHandle(songNum);
        if (handle != NULL) {
            Knife_Sound_Handle_volume(handle, 0x7f, level);
            Knife_Sound_Handle_pause(handle, 0);
        } else {
            m4aSongNumStart(songNum);
        }
    }
}
