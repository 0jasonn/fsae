#ifndef ENGINE_SNDHEAP_OWNER_API_H
#define ENGINE_SNDHEAP_OWNER_API_H

// Functions defined in src/engine/sndheap_owner*.cpp.

#include "engine/entity.h"

extern "C" {
void *SndHeapOwner_AllocFromHeap(u32 *owner, u32 size);
void *SndHeapOwner_Allocate(u32 *owner, u32 size);
void SndHeapOwner_Free(u32 *owner, u8 *block);
void SndHeapOwner_FreeToHeap(u32 *owner, u32 block);
void SndHeapOwner_NoOp(void);
void *SndHeapOwner_Reserve(u32 *owner, u32 size);
void *SndHeapOwner_Reset(u32 *owner);
void *SndHeapOwner_TryReserve(u32 *owner, u32 size);
}

#endif
