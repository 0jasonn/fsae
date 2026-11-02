#ifndef WIP_C_SOUND_REQ_H
#define WIP_C_SOUND_REQ_H

#include "engine/entity.h"

// Sound request state (soundVolumeState, 0x02176270), same bytes as SoundVolumeState in src/actor/object/sound.cpp
typedef struct SoundReqState {
    /* 00 */ u16 volume;
    /* 02 */ u16 currentSong; // song of the last request, target of the 0x8002xxxx.. commands
    /* 04 */ u8 enabled;
    /* 05 */ u8 unk_05[3];
} SoundReqState;
extern SoundReqState soundVolumeState;

extern u8 data_0212c4f8; // nonzero blocks all sound requests

// Song to sound group tables read when a song is started
typedef struct SongGroupRef {
    /* 00 */ u16 groupIndex;
    /* 02 */ u8 unk_02[6];
} SongGroupRef;
typedef struct SoundGroup {
    /* 00 */ const void *entry;
    /* 04 */ u8 unk_04[8];
} SoundGroup;
extern const SongGroupRef songGroupRefs[]; // 0x020dd99c, indexed by song number
extern const SoundGroup soundGroups[];     // 0x020dd9a0

extern "C" {
void SoundVSyncOff_rev01(void);
void SoundVSyncOn_rev01(void);
void SoundNop_0208d5d0(const void *entry); // 0x0208d5d0, empty; the caller passes the group entry (m4a_vsync_api.h declares it without argument)
}

#endif
