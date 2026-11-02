#include "engine/functions.h"
#include "global.h"
#include "engine/sound/m4a.h"
#include "engine/sound/m4a_api.h"
#include "actor/object/sound_api.h"
#include "actor/object/sound_req.h"

// Sound module (module sound). Address -> name:
//   0x02076fe0 SoundReq (original name): song / sound request. Plain ids start a song and set the volume; ids with bit 31
//   set are commands (stop, volume, continue, vsync off/on, start with group setup), selected by the upper half.

void SoundReq(u32 request) {
    SoundReqState *state = &soundVolumeState;
    u16 vol;

    if (data_0212c4f8 != 0) {
        return;
    }
    if (request & 0x80000000) {
        switch (request & 0xffff0000) {
        case 0x80010000:
            state->currentSong = 0;
            m4aMPlayAllStop();
            break;
        case 0x80020000:
            m4aSongNumStop(state->currentSong);
            break;
        case 0x80030000:
            break;
        case 0x80040000:
            vol = (u16)request;
            if (vol == 0) {
                vol = 4;
            }
            if (state->enabled != 0) {
                m4aSongNumSetParam(state->currentSong, 0xffff, 0);
            } else {
                m4aSongNumSetVolume(state->currentSong, vol);
            }
            break;
        case 0x80050000:
            vol = (u16)request;
            if (vol == 0) {
                vol = 4;
            }
            m4aSongNumContinue(state->currentSong, vol);
            break;
        case 0x80060000:
            m4aSongNumSetPlayerValue(state->currentSong, (u16)request);
            break;
        case 0x80070000:
            SoundVSyncOff_rev01();
            break;
        case 0x80080000:
            m4aSongNumSetVolume(state->currentSong, 0);
            break;
        case 0x80090000:
            SoundVSyncOn_rev01();
            // fall through
        case 0x800a0000:
            if (state->currentSong != 0) {
                m4aSongNumStartOrContinue(state->currentSong);
            }
            break;
        case 0x800b0000:
            state->currentSong = request;
            func_0208d260(state->currentSong);
            if (state->enabled != 0) {
                volumeSet(request);
            } else {
                SoundNop_0208d5d0(soundGroups[songGroupRefs[state->currentSong].groupIndex].entry);
                m4aSongNumSetParam(state->currentSong, 0xffff, 0);
                m4aSongNumContinue(state->currentSong, 4);
            }
            break;
        case 0x800c0000:
            state->currentSong = request;
            m4aSongNumStartOrContinue(state->currentSong);
            if (state->enabled != 0) {
                volumeSet(request);
            } else {
                SoundNop_0208d5d0(soundGroups[songGroupRefs[state->currentSong].groupIndex].entry);
                m4aSongNumSetParam(state->currentSong, 0xffff, 0);
                m4aSongNumContinue(state->currentSong, 4);
            }
            break;
        case 0x800d0000:
            m4aSongNumStart((u16)request);
            volumeSet(request);
            break;
        }
    } else if (request != 0) {
        if (request >= 0x190 && request <= 0x1f3) {
            state->currentSong = (u16)request;
            func_0208d260((u16)request);
        } else {
            m4aSongNumStart((u16)request);
        }
        volumeSet(request);
    }
}
