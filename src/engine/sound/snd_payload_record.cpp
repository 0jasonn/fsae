#include "engine/functions.h"
#include "engine/sound/sndlink.h"
#include "engine/sound/sndrecord.h"
#include "engine/sound/snd_payload_record.h"

extern "C" void *SndHeap_ReserveLinear(u32 *heap, u32 size, s32 alignment);

void *func_020c0b20(void *record, u32 size, void *callback, void *data, s32 index2) {
    SndRecord *owner = (SndRecord *)record;
    SndPayloadRecordBlock *block;
    u32 allocationSize;
    SndList *list;

    allocationSize = (size + 0x1f) & ~0x1f;
    block = (SndPayloadRecordBlock *)SndHeap_ReserveLinear((u32 *)owner->heap, allocationSize + 0x20, 0x20);
    if (block == NULL) {
        return NULL;
    }
    list = (SndList *)owner->list;
    list = (SndList *)SndList_GetPrev(list, NULL);
    block->size = size;
    block->callback = callback;
    block->callbackData = data;
    block->callbackIndex = index2;
    SndList_Append(list, (u8 *)block);
    return (u8 *)block + 0x20;
}
