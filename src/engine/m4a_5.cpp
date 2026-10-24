#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/m4a.h"
#include "engine/knife_sound_4.h"

// m4aSongNumIsPlaying (0x0208d8a4): whether the song with the given number is playing. Wave numbers 0x1ea to 0x1f3 check
// the first wave slot.
extern "C" u32 m4aSongNumIsPlaying(u16 songNum);
ARM u32 m4aSongNumIsPlaying(u16 songNum) {
    Knife::Sound::WaveHandle *wave;
    void *handle;

    if (songNum >= 0x1ea && songNum < 0x1f4) {
        wave = (Knife::Sound::WaveHandle *)Knife_Sound_System_getWaveHandle(0);
        if (wave->isValid() != 0) {
            if (songNum == *(s32 *)((u8 *)wave + 0x4)) {
                return 1;
            }
        }
        return 0;
    }
    handle = Knife_Sound_System_findHandle(songNum);
    if (handle != NULL) {
        if (((KnifeSoundSequenceHandle *)handle)->isValid() != 0) {
            return 1;
        }
    }
    return 0;
}

// GX_GetSizeOfOBJ (0x0208d92c): the volume of the current wave song (tail call of MPlayGetVolume, parked)
extern "C" u16 GX_GetSizeOfOBJ(void);
ARM u16 GX_GetSizeOfOBJ(void) {
    return MPlayGetVolume(((M4aSoundTable *)&data_02176238)->waveId);
}

// m4aMusicSetVolume (0x0208d944): sets the parameter of the current wave song (tail call of m4aSongNumSetParam)
extern "C" void m4aMusicSetVolume(u16 a, u16 b);
ARM void m4aMusicSetVolume(u16 a, u16 b) {
    m4aSongNumSetParam(((M4aSoundTable *)&data_02176238)->waveId, a, b);
}

// m4aEnterManual (0x0208d968): stops the music, updates the sound system and sets the master volume and both wave
// volumes to the maximum
extern "C" void m4aEnterManual(void);
ARM void m4aEnterManual(void) {
    m4aMPlayAllStop();
    Knife_Sound_System_update();
    Menu_SetMasterVolume(0x7f);
    SndTable_SetByte8(0, 0x7f);
    SndTable_SetByte8(1, 0x7f);
    SndMaster_SetPan(0);
}

// m4aEnterManualAlias (0x0208d9a8): alias of m4aEnterManual, tail call
extern "C" void m4aEnterManualAlias(void);
ARM void m4aEnterManualAlias(void) {
    m4aEnterManual();
}

// m4aSoundResume (0x0208d9b4): resumes the sound system (pause off)
extern "C" void m4aSoundResume(void);
ARM void m4aSoundResume(void) {
    Knife_Sound_System_pause(0);
}

// loadFile (0x0208d9c4): reads a whole file into memory from the EL global area, aligned as given. The size goes to *size;
// returns the block, or NULL when the file cannot be opened or read in full.
extern "C" void *loadFile(u32 *size, const char *path, s32 align);
ARM void *loadFile(u32 *size, const char *path, s32 align) {
    u8 file[0x48];
    u32 length;
    void *buffer;

    if (GzFile_open(file, path) == 1) {
        length = GzFile_getLength(file);
        *size = length;
        buffer = EL_GetGlobalAdr(length, align);
        if (*size != GzFile_read(file, buffer, *size)) {
            func_0208e188(buffer);
            buffer = NULL;
        }
        GzFile_close(file);
    } else {
        return NULL;
    }
    return buffer;
}
