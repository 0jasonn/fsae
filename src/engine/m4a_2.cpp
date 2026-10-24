#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/m4a.h"

// m4a song stop helpers, 0x0208d52c to 0x0208d5d0 (the m4a_vsync pair follows at 0x0208d5d0).

// m4aSongNumStop (0x0208d52c): stops the song with the given number. Numbers 0x1ea to 0x1f3 stop both wave slots;
// other numbers stop their handle, and clear the pending wave id when the handle has no player number.
extern "C" void m4aSongNumStop(u16 songNum);
ARM void m4aSongNumStop(u16 songNum) {
    s32 i;
    void *handle;

    if (songNum >= 0x1ea && songNum < 0x1f4) {
        for (i = 0; i < 2; i++) {
            Knife_Sound_Handle_stop(Knife_Sound_System_getWaveHandle(i), 0, 0);
        }
        ((M4aSoundTable *)&data_02176238)->waveId = 0;
        return;
    }
    handle = Knife_Sound_System_findHandle(songNum);
    if (handle == NULL) {
        return;
    }
    if (Knife_Sound_SequenceHandle_getPlayerNumber(handle) == 0) {
        ((M4aSoundTable *)&data_02176238)->waveId = 0;
    }
    Knife_Sound_Handle_stop(handle, 0, 0);
}

// m4aMPlayAllStop (0x0208d5b4): stops every sound and clears the pending wave id
extern "C" void m4aMPlayAllStop(void);
ARM void m4aMPlayAllStop(void) {
    Knife_Sound_System_fwd_08c630();
    ((M4aSoundTable *)&data_02176238)->waveId = 0;
}
