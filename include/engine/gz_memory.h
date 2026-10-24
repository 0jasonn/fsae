#ifndef WIP_D_GZ_MEMORY_H
#define WIP_D_GZ_MEMORY_H

#include "types.h"

namespace Gz {
namespace Memory {

// Gz::Memory::GzAllocator: a heap (the heap pointer is at +0) over a block taken from the main arena
typedef struct GzAllocator {
    /* 00 */ void *heap;
} GzAllocator;

}
}

extern "C" {
// Arena and heap calls (dsd names where the library name is not known)
void *OS_GetArenaLo(s32 arena);
void *OS_GetArenaHi(s32 arena);
void *OS_AllocFromArenaLo(s32 arena, u32 size, u32 align);
void *func_020c2694(void *block, u32 size, s32 flags);
void *func_020c26cc(void *heap, u32 size, u32 align);
void func_020c26fc(void *heap, void *block, s32 flags);
void Gz_Memory_GzAllocator_init(Gz::Memory::GzAllocator *self, s32 unused);
void *func_0208e148(u32 size);
void func_0208e138(void *allocator);
extern Gz::Memory::GzAllocator *data_021770a4; // the global allocator that EL_GetGlobalAdr and the wrappers use
}

#endif
