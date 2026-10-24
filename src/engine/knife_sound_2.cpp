#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/knife_sound.h"

// Knife::Sound::System pause and the sequence handle helpers, 0x0208c5f0 to 0x0208c6b4.
// Provisional names in scratch/agentD/renames.txt: Knife_Sound_System_fwd_08c630 to Knife_Sound_System_destroyWaveHandles.

extern "C" void Knife_Sound_System_pause(s32 pause);
ARM void Knife_Sound_System_pause(s32 pause) {
    int i;
    Knife_Sound_HandleFactory_pause(&data_02171f74, pause);
    for (i = 0; i < 2; i++) {
        Knife_Sound_Handle_pause(&data_02171e74[i], pause);
    }
}

extern "C" void Knife_Sound_System_fwd_08c630(void);
ARM void Knife_Sound_System_fwd_08c630(void) {
    func_020bf25c();
}

extern "C" KnifeSoundSequenceHandle *Knife_Sound_System_createHandle(void);
ARM KnifeSoundSequenceHandle *Knife_Sound_System_createHandle(void) {
    return Knife_Sound_HandleFactory_create(&data_02171f74);
}

extern "C" void Knife_Sound_System_releaseHandle(KnifeSoundSequenceHandle *handle);
ARM void Knife_Sound_System_releaseHandle(KnifeSoundSequenceHandle *handle) {
    Knife_Sound_HandleFactory_release(&data_02171f74, handle);
}

extern "C" KnifeSoundSequenceHandle *Knife_Sound_System_findHandle(u32 id);
ARM KnifeSoundSequenceHandle *Knife_Sound_System_findHandle(u32 id) {
    return Knife_Sound_HandleFactory_find(&data_02171f74, id);
}

extern "C" KnifeSoundWaveHandle *Knife_Sound_System_getWaveHandle(s32 index);
ARM KnifeSoundWaveHandle *Knife_Sound_System_getWaveHandle(s32 index) {
    return &data_02171e74[index];
}

extern "C" void Knife_Sound_System_destroyWaveHandles(void);
ARM void Knife_Sound_System_destroyWaveHandles(void) {
    func_0200c868(data_02171e74, 2, sizeof(KnifeSoundWaveHandle), (void *)Knife_Sound_WaveHandle_dtor_WaveHandle_0904e0);
}
