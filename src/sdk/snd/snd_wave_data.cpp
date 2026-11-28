#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/dc_cache.h"
#include "sdk/snd/mutex_wrap_api.h"
#include "sdk/snd/snd_bank.h"

// SND_SetWaveDataAddress(waveArc, waveNo, address) (0x0201bdfc): stores the address (or offset) of one wave and flushes
// that table entry.
void SND_SetWaveDataAddress(SndWaveArc *waveArc, s32 waveNo, u32 address) {
    Mutex_LockGlobal();
    waveArc->waveAddress[waveNo] = address;
    DC_StoreRange(&waveArc->waveAddress[waveNo], 4);
    Mutex_UnlockGlobal();
}

// SND_GetWaveDataAddress(waveArc, waveNo) (0x0201be30): address of one wave; table entries below 0x2000000 are offsets
// from the archive and get the archive address added, 0 stays 0.
const void *SND_GetWaveDataAddress(SndWaveArc *waveArc, s32 waveNo) {
    u32 address;
    u32 result;

    Mutex_LockGlobal();
    address = waveArc->waveAddress[waveNo];
    if (address != 0) {
        if (address < 0x2000000) {
            result = (u32)waveArc + address;
        } else {
            result = address;
        }
    } else {
        result = 0;
    }
    Mutex_UnlockGlobal();
    return (const void *)result;
}
