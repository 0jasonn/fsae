#include "engine/functions.h"
#include "global.h"

extern "C" {
void *SndHeap_Allocate(u32 *heap, u32 size, s32 flag);
void SndHeap_Free(u32 *heap, u8 *block);
void *SndHeap_ReserveLinear(u32 heap, u32 size, u32 flag);
void *SndHeapPool_Alloc(u32 heap, u32 size);
void *SndHeapPool_Push(u32 heap);
void *OS_AllocFromHeap(u32 heap, void *ptr, u32 size);
void OS_FreeToHeap(u32 heap, void *ptr, u32 block);
}

// The owner keeps the heap at +4 and an allocation flag at +8 (the owner itself is passed in r0).
// Allocates from the owner's heap with its flag.
extern "C" void *SndHeapOwner_Allocate(u32 *owner, u32 size);
ARM void *SndHeapOwner_Allocate(u32 *owner, u32 size) {
    return SndHeap_Allocate((u32 *)owner[1], size, owner[2]);
}

// Frees a block of the owner's heap.
extern "C" void SndHeapOwner_Free(u32 *owner, u8 *block);
ARM void SndHeapOwner_Free(u32 *owner, u8 *block) {
    SndHeap_Free((u32 *)owner[1], block);
}

// Reserves size bytes at the owner's heap with its flag (through SndHeap_ReserveLinear).
extern "C" void *SndHeapOwner_Reserve(u32 *owner, u32 size);
ARM void *SndHeapOwner_Reserve(u32 *owner, u32 size) {
    return SndHeap_ReserveLinear(owner[1], size, owner[2]);
}

// Empty hook (no work).
extern "C" void SndHeapOwner_NoOp(void);
ARM void SndHeapOwner_NoOp(void) {
}

// Reserves size bytes when the heap at the owner has room for them (through SndHeapPool_Alloc), otherwise returns 0.
extern "C" void *SndHeapOwner_TryReserve(u32 *owner, u32 size);
ARM void *SndHeapOwner_TryReserve(u32 *owner, u32 size) {
    u32 *heap;

    heap = (u32 *)owner[1];
    if (size > heap[10]) {
        return 0;
    }
    return SndHeapPool_Alloc((u32)heap, size);
}

// Resets the owner's heap (through SndHeapPool_Push).
extern "C" void *SndHeapOwner_Reset(u32 *owner);
ARM void *SndHeapOwner_Reset(u32 *owner) {
    return SndHeapPool_Push(owner[1]);
}

// Allocates from the operating system heap of the owner (OS_AllocFromHeap).
extern "C" void *SndHeapOwner_AllocFromHeap(u32 *owner, u32 size);
ARM void *SndHeapOwner_AllocFromHeap(u32 *owner, u32 size) {
    return OS_AllocFromHeap(owner[2], (void *)owner[1], size);
}

// Returns a block to the operating system heap of the owner (OS_FreeToHeap).
extern "C" void SndHeapOwner_FreeToHeap(u32 *owner, u32 block);
ARM void SndHeapOwner_FreeToHeap(u32 *owner, u32 block) {
    OS_FreeToHeap(owner[2], (void *)owner[1], block);
}
