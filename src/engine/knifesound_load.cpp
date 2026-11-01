#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/knifesound_player.h"

// Knife::Sound::DataManager loaders (0x0208be04, 0x0208be58). The manager's first word is the archive; the heap's
// first word is passed on to the sound system.
//   0x0208be04 Knife_Sound_DataManager_loadGroup, 0x0208be58 Knife_Sound_DataManager_loadSequence
extern const char data_0211ab2c[];
extern const char data_0211ab34[];
extern const char data_0211aaf2[];
extern const char data_0211ab44[];
extern const char data_0211ab4c[];
extern const char data_0211aafc[];

// Loads group into the archive, after checking that the manager has one
void Knife_Sound_DataManager_loadGroup(void *manager, s32 group, void *heap) {
    if (*(void **)manager == NULL) {
        Engine_AssertFail(data_0211ab2c, data_0211ab34, data_0211aaf2, 0x2b);
    }
    Knife_Sound_Archive_apply(*(void **)manager);
    SSP_GetDateTime(group, *(s32 *)heap);
}

// Loads the sequence into the archive, after checking that the manager has one; returns the sound system's result
s32 Knife_Sound_DataManager_loadSequence(void *manager, s32 seq, void *heap) {
    if (*(void **)manager == NULL) {
        Engine_AssertFail(data_0211ab44, data_0211ab4c, data_0211aafc, 0x32);
    }
    Knife_Sound_Archive_apply(*(void **)manager);
    return SndSys_CheckValue((void *)seq, *(s32 *)heap);
}
