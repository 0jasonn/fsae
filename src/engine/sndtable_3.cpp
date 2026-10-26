#include "engine/functions.h"
#include "global.h"
#include "engine/sndrecord.h"

extern "C" {
extern u8 *data_021848b0; // sound state pointer
void *SndHeap_InitLinear(void *base, u32 size, s32 flags);
void Menu_ForwardC28b0(void *heap);
}

// SndHeap_CreateRecord: makes a record at the 4-byte aligned start of [base, base + size). Its heap is the rest of the range
// after a 0x10-byte header. Returns the record, or 0 when the range is too small or the heap could not be made.
extern "C" void *SndHeap_CreateRecord(void *base, s32 size);
ARM void *SndHeap_CreateRecord(void *base, s32 size) {
    u32 rounded;
    u32 start;
    u32 end;
    u32 avail;
    void *heap;

    rounded = (u32)base + 3;
    end = (u32)base + size;
    start = rounded & ~3;
    if (start > end) {
        return 0;
    }
    avail = end - start;
    if (avail < 0x10) {
        return 0;
    }
    heap = SndHeap_InitLinear((void *)(start + 0x10), avail - 0x10, 0);
    if (heap == 0) {
        return 0;
    }
    if (SndRecord_Create((SndRecord *)start, heap) != 0) {
        return (void *)start;
    }
    Menu_ForwardC28b0(heap);
    return 0;
}

// SndRecord_Free: clears the record and frees its heap.
extern "C" void SndRecord_Free(SndRecord *record);
ARM void SndRecord_Free(SndRecord *record) {
    SndRecord_Clear(record);
    Menu_ForwardC28b0(record->heap);
}
