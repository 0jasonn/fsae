#ifndef ENGINE_SNDHEAP_LINEAR_API_H
#define ENGINE_SNDHEAP_LINEAR_API_H

// Functions defined in src/engine/sndheap_linear*.cpp.

#include "engine/entity.h"

extern "C" {
void *SndHeapPool_Pop(void **head);
void SndHeap_ResetFlags(u32 *heap, u32 flags);
void SndHeap_ResetHigh(u32 *heap);
void SndHeap_Rewind(u32 *heap);
}

#endif
