#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/sound/knifesound_player.h"

// Knife::Sound::ArchivePlayer sequence starters (0x0208bd34, 0x0208bda8). Each takes a new sequence handle from the
// system, starts an entry on its player, and keeps the handle (its id is the last argument) or releases it.
//   0x0208bd34 Knife_Sound_ArchivePlayer_startSequenceArchive, 0x0208bda8 Knife_Sound_ArchivePlayer_startSequence

// Starts the archive entry (a, b, c, d, e) on the handle's player; returns the handle, or NULL when the start fails.
void *Knife_Sound_ArchivePlayer_startSequenceArchive(void *self, s32 a, s32 b, s32 c, s32 d, s32 e) {
    void *handle;

    handle = Knife_Sound_System_createHandle();
    if (handle != NULL) {
        if (SndState_StartEntryEx((u8 *)Knife_Sound_SequenceHandle_getPlayerField(handle), a, b, c, (void *)d, e) == 0) {
            Knife_Sound_System_releaseHandle(handle);
            return NULL;
        }
        *(s32 *)((u8 *)handle + 4) = e;
    }
    return handle;
}

// Starts the entry b on the handle's player; returns the handle, or NULL when the start fails.
void *Knife_Sound_ArchivePlayer_startSequence(void *self, s32 a, s32 b) {
    void *handle;

    handle = Knife_Sound_System_createHandle();
    if (handle != NULL) {
        if (SndState_StartEntry(Knife_Sound_SequenceHandle_getPlayerField(handle), b) == 0) {
            Knife_Sound_System_releaseHandle(handle);
            return NULL;
        }
        *(s32 *)((u8 *)handle + 4) = b;
    }
    return handle;
}
