#include "engine/functions.h"
#include "global.h"
#include "engine/sndrecord.h"
#include "engine/sndlist.h"

extern "C" {
void *func_020c28bc(void *heap, s32 size, s32 align);
void SND_FlushCommand(u32 mode);
void SND_WaitForCommandProc(u32 tag);
u32 SND_GetCurrentCommandTag(void);
}

// SndList_Reset: resets the count of a list (it is SndList_Init with a count of zero).
extern "C" void SndList_Reset(void *list);
ARM void SndList_Reset(void *list) {
    SndList_Init((SndList *)list, 0);
}

// SndRecord_Create: sets the heap of a record, resets its list to 12 entries and allocates the first entry. Returns 1
// when the entry could be allocated.
extern "C" s32 SndRecord_Create(SndRecord *record, void *heap);
ARM s32 SndRecord_Create(SndRecord *record, void *heap) {
    SndList_Init((SndList *)record->list, 0xc);
    record->heap = heap;
    return SndRecord_Alloc(record) != 0;
}

// SndRecord_Alloc: allocates a 0x14-byte entry from the record's heap, resets it and adds it to the list. Returns 1 when
// the entry was allocated, 0 otherwise.
extern "C" s32 SndRecord_Alloc(SndRecord *record);
ARM s32 SndRecord_Alloc(SndRecord *record) {
    void *entry;

    entry = func_020c28bc(record->heap, 0x14, 4);
    if (entry == 0) {
        return 0;
    }
    SndList_Reset(entry);
    SndList_Append((SndList *)record->list, (u8 *)entry);
    return 1;
}

// SndSys_FlushAndWait: takes the current command tag, flushes the command queue and waits for that command.
extern "C" void SndSys_FlushAndWait(void);
ARM void SndSys_FlushAndWait(void) {
    u32 tag;

    tag = SND_GetCurrentCommandTag();
    SND_FlushCommand(1);
    SND_WaitForCommandProc(tag);
}
