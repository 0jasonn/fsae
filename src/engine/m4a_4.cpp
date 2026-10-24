#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/m4a.h"

// m4a song parameter helpers, 0x0208d790 to 0x0208d830.

// m4aSongNumSetPlayerValue (0x0208d790): forwards a value to the sequence player of a song that is not a wave slot
// (numbers 0x1ea to 0x1f3 do nothing)
extern "C" void m4aSongNumSetPlayerValue(u16 songNum, s32 value);
ARM void m4aSongNumSetPlayerValue(u16 songNum, s32 value) {
    void *handle;

    if (songNum >= 0x1ea && songNum < 0x1f4) {
        return;
    }
    handle = Knife_Sound_System_findHandle(songNum);
    if (handle == NULL) {
        return;
    }
    Knife_Sound_SequenceHandle_fwdPlayer_08c4a0(handle, value);
}

// m4aSongNumSetParam (0x0208d7c8): sets the parameter of both wave slots (numbers 0x1ea to 0x1f3) or of the song handle.
// The second argument is not read.
extern "C" void m4aSongNumSetParam(u16 songNum, u16 unused, s32 param);
ARM void m4aSongNumSetParam(u16 songNum, u16 unused, s32 param) {
    s32 i;
    void *handle;

    if (songNum >= 0x1ea && songNum < 0x1f4) {
        for (i = 0; i < 2; i++) {
            Knife_Sound_Handle_volume(Knife_Sound_System_getWaveHandle(i), param, 0);
        }
        return;
    }
    handle = Knife_Sound_System_findHandle(songNum);
    if (handle == NULL) {
        return;
    }
    Knife_Sound_Handle_volume(handle, param, 0);
}
