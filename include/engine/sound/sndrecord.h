#ifndef ENGINE_SOUND_SNDRECORD_H
#define ENGINE_SOUND_SNDRECORD_H

#include "engine/functions.h"
#include "global.h"

// Record with the heap it allocates from at +0 and a list at +4.
typedef struct SndRecord {
    /* 00 */ void *heap;
    /* 04 */ u8 list[0x18 - 0x04];
} SndRecord;

extern "C" s32 SndRecord_Create(SndRecord *record, void *heap);
extern "C" s32 SndRecord_Alloc(SndRecord *record);
extern "C" void SndRecord_Clear(SndRecord *record);
extern "C" {
void *SndHeap_CreateRecord(void *base, u32 size);
void *func_020c0b20(void *record, u32 size, void *callback, void *data, s32 index2);
void SndList_Reset(void *list);
void SndSys_FlushAndWait(void);
}

#endif
