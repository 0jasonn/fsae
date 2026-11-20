#ifndef WIP_C_KNIFESOUND_PLAYER_H
#define WIP_C_KNIFESOUND_PLAYER_H

// Knife::Sound code around 0x0208bd34 .. 0x0208beac: the sequence starters and the DataManager loaders.
// Functions defined in src/wip/C/knifesound_seq.cpp and src/wip/C/knifesound_load.cpp.

#include "engine/functions.h"

// Calls into other units (plain names, so C linkage)
extern "C" {
void Engine_AssertFail(const char *file, const char *expr, const char *msg, s32 line);
void *Knife_Sound_System_createHandle(void);
void Knife_Sound_System_releaseHandle(void *handle);
void *Knife_Sound_SequenceHandle_getPlayerField(void *handle);
BOOL SSP_GetDateTime(u32 id, u32 value);
}

// Functions defined in this module
extern "C" {
void *Knife_Sound_ArchivePlayer_startSequenceArchive(void *self, s32 a, s32 b, s32 c, s32 d, s32 e);
void *Knife_Sound_ArchivePlayer_startSequence(void *self, s32 a, s32 b);
void Knife_Sound_DataManager_loadGroup(void *manager, s32 group, void *heap);
s32 Knife_Sound_DataManager_loadSequence(void *manager, s32 seq, void *heap);
}

#endif
