#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/m4a.h"
#include "engine/knife_sound_4.h"

// m4aSongNumStart (0x0208d118). The function after it (func_0208d260) is not matched yet.

// m4aSongNumStart (0x0208d118): starts the song with the given number. Numbers 0x190 to 0x1f3 go to func_0208d260. The
// other numbers index the loaded-song bitmap; a loaded song is played through the handle that already exists, otherwise
// a new sequence handle is created and tagged with the number.
extern "C" void pauseWavePlayer(s32 pause);
extern "C" u32 func_0208d260(u32 songNum);
extern "C" u32 m4aSongNumStart(u16 songNum);
ARM u32 m4aSongNumStart(u16 songNum) {
    s32 index;
    s32 flag;
    void *handle;
    s32 valid;

    flag = -1;
    if (songNum >= 0x1f5) {
        index = songNum - 0x12d;
    } else if (songNum >= 0x190 && songNum <= 0x1f3) {
        return func_0208d260(songNum);
    } else {
        if (songNum >= 0xc9) {
            index = songNum - 0xc9;
            flag = 0;
        } else {
            index = songNum - 1;
            if (songNum == 0xf) {
                ((M4aSoundTable *)&data_02176238)->delay = 0x6c;
                if (((M4aSoundTable *)&data_02176238)->waveId >= 0x1ea && ((M4aSoundTable *)&data_02176238)->waveId < 0x1f4) {
                    pauseWavePlayer(1);
                } else {
                    handle = Knife_Sound_System_findHandle(((M4aSoundTable *)&data_02176238)->waveId);
                    if (handle != NULL) {
                        Knife_Sound_Handle_pause(handle, 1);
                    }
                }
            }
        }
    }
    if (((M4aSoundTable *)&data_02176238)->bitmap != NULL) {
        u8 mapByte = ((M4aSoundTable *)&data_02176238)->bitmap[index / 8];
        if (mapByte & (u8)(1 << (index % 8))) {
            handle = Knife_Sound_System_findHandle(songNum);
            if (handle != NULL) {
                return (u32)handle;
            }
        }
    }
    handle = Knife_Sound_ArchivePlayer_startSequenceArchive(data_02176239, -1, -1, flag, 0, index);
    if (handle == NULL) {
        return (u32)handle;
    }
    valid = ((KnifeSoundSequenceHandle *)handle)->isValid();
    if (valid != 0) {
        ((KnifeSoundSequenceHandle *)handle)->id = songNum;
    }
    return valid;
}
