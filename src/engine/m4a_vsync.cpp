#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Sound helpers after the m4a driver, 0x0208d5d0 to 0x0208d610: an empty callback, an empty function from functions.h,
// and the VSync on/off pair (which pause the Knife sound system and the wave player).
// SoundNop_0208d5d0 is provisional: SoundNop_0208d5d0 in scratch/agentD/renames.txt.

extern "C" void Knife_Sound_System_pause(s32 pause);
extern "C" void pauseWavePlayer(s32 pause);

// SoundNop_0208d5d0 (0x0208d5d0): does nothing
extern "C" void SoundNop_0208d5d0(void);
ARM void SoundNop_0208d5d0(void) {
}

// func_0208d5d4 (0x0208d5d4): does nothing; declared in functions.h
ARM void func_0208d5d4(void) {
}

// SoundVSyncOff_rev01 (0x0208d5d8): pauses the sound system and the wave player
extern "C" void SoundVSyncOff_rev01(void);
ARM void SoundVSyncOff_rev01(void) {
    Knife_Sound_System_pause(1);
    pauseWavePlayer(1);
}

// SoundVSyncOn_rev01 (0x0208d5f4): resumes the sound system and the wave player
extern "C" void SoundVSyncOn_rev01(void);
ARM void SoundVSyncOn_rev01(void) {
    Knife_Sound_System_pause(0);
    pauseWavePlayer(0);
}
