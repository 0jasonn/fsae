#include "engine/functions.h"
#include "engine/sound/sndheap_linear_api.h"
#include "engine/sound/sndlink.h"
#include "engine/sound/sndrecord.h"
#include "engine/sound/snd_payload_record.h"

typedef void (*SndPayloadRecordCallback)(void *payload, u32 size, void *data, s32 index);

// SndRecord_Clear: calls each payload callback while walking each record entry and its payload list backwards, then
// resets the record heap and rebuilds its initial entry. The command queue is flushed only when a callback ran.
void SndRecord_Clear(SndRecord *record) {
    SndList *list;
    u8 *entry;
    s32 callbackCalled;
    u8 *payload;
    SndPayloadRecordBlock *block;
    SndPayloadRecordCallback callback;

    list = (SndList *)record->list;
    callbackCalled = 0;
    entry = SndList_GetPrev(list, 0);
    while (entry != 0) {
        payload = SndList_GetPrev((SndList *)entry, 0);
        while (payload != 0) {
            block = (SndPayloadRecordBlock *)payload;
            callback = (SndPayloadRecordCallback)block->callback;
            if (callback != 0) {
                callback(payload + 0x20, block->size, block->callbackData, block->callbackIndex);
                callbackCalled = 1;
            }
            payload = SndList_GetPrev((SndList *)entry, payload);
        }
        LinkList_Remove(list, entry);
        entry = SndList_GetPrev(list, 0);
    }
    SndHeap_ResetFlags((u32 *)record->heap, 3);
    if (callbackCalled != 0) {
        SndSys_FlushAndWait();
    }
    SndRecord_Alloc(record);
}
