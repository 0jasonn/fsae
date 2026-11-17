#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/sound/m4a.h"
#include "knife/sound/knife_sound_4.h"

// Knife_Sound_System_update (0x0208c554): per-frame update of the sequence handle factory and the two wave handles,
// then the driver buffer swap and, when it succeeded, a refresh of the 16 channel info records.
void Knife_Sound_System_update(void) {
    s32 i;
    s32 j;
    Knife::Sound::WaveHandle *wave;
    s32 channel;

    Knife_Sound_HandleFactory_update(&data_02171f74);
    for (i = 0; i < 2; i++) {
        Knife_Sound_Handle_update(&data_02171e74[i]);
    }
    SndSys_Shutdown();
    for (j = 0; j < 2; j++) {
        wave = (Knife::Sound::WaveHandle *)&data_02171e74[j];
        if (!wave->Knife::Sound::WaveHandle::isValid()) {
            wave->finalize();
        }
    }
    if (SndSys_SwapDriverBuffer()) {
        for (channel = 0; channel < 16; channel++) {
            SndSys_ReadChannelInfoCurrent(channel, data_02171eb4 + channel * 0xc);
        }
    }
}
