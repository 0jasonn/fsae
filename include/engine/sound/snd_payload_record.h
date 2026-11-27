#ifndef ENGINE_SOUND_SND_PAYLOAD_RECORD_H
#define ENGINE_SOUND_SND_PAYLOAD_RECORD_H

#include "engine/sound/sndlink.h"
#include "engine/sound/sndrecord.h"

// A payload begins 0x20 bytes after this node. Its owning list has link stride zero.
typedef struct SndPayloadRecordBlock {
    SndLink link;          // 0x00
    u32 size;              // 0x08
    void *callback;        // 0x0c
    void *callbackData;    // 0x10
    s32 callbackIndex;     // 0x14
    u32 unknown_18[2];
} SndPayloadRecordBlock;

#endif
