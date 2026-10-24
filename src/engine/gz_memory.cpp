#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/gz_memory.h"

// Gz::Memory::GzAllocator, the global allocator wrappers and EL_GetGlobalAdr, 0x0208e05c to 0x0208e1a4.
// func_0208e138 and func_0208e148 keep their names: other units call them. The allocator functions keep their dsd
// suffixes because the overloads of alloc would otherwise share one plain name.

#define REG_IME (*(volatile u16 *)0x04000208)

// GzAllocator::init (0x0208e05c): takes the main arena (16-byte aligned) and makes a heap over it
extern "C" void Gz_Memory_GzAllocator_init(Gz::Memory::GzAllocator *self, s32 unused);
ARM void Gz_Memory_GzAllocator_init(Gz::Memory::GzAllocator *self, s32 unused) {
    void *arenaLo;
    void *arenaHi;
    u32 size;
    void *block;

    arenaLo = OS_GetArenaLo(0);
    arenaHi = OS_GetArenaHi(0);
    size = ((u32)arenaHi & ~0xf) - (((u32)arenaLo + 0xf) & ~0xf);
    block = OS_AllocFromArenaLo(0, size, 16);
    self->heap = func_020c2694(block, size, 2);
}

// GzAllocator::alloc(unsigned long) (0x0208e0b0): allocates with alignment 4, with interrupts disabled around the call
extern "C" void *Gz_Memory_GzAllocator_alloc_08e0b0(Gz::Memory::GzAllocator *self, u32 size);
ARM void *Gz_Memory_GzAllocator_alloc_08e0b0(Gz::Memory::GzAllocator *self, u32 size) {
    u16 ime;
    void *block;

    ime = REG_IME;
    REG_IME = 0;
    block = func_020c26cc(self->heap, size, 4);
    (void)REG_IME;
    REG_IME = ime;
    return block;
}

// GzAllocator::alloc(unsigned long, long) (0x0208e0e0): same as above with the alignment given
extern "C" void *Gz_Memory_GzAllocator_alloc_08e0e0(Gz::Memory::GzAllocator *self, u32 size, s32 align);
ARM void *Gz_Memory_GzAllocator_alloc_08e0e0(Gz::Memory::GzAllocator *self, u32 size, s32 align) {
    u16 ime;
    void *block;

    ime = REG_IME;
    REG_IME = 0;
    block = func_020c26cc(self->heap, size, align);
    (void)REG_IME;
    REG_IME = ime;
    return block;
}

// GzAllocator::dealloc(void*) (0x0208e10c): frees a block with interrupts disabled
extern "C" void Gz_Memory_GzAllocator_dealloc(Gz::Memory::GzAllocator *self, void *block);
ARM void Gz_Memory_GzAllocator_dealloc(Gz::Memory::GzAllocator *self, void *block) {
    u16 ime;

    ime = REG_IME;
    REG_IME = 0;
    func_020c26fc(self->heap, block, 0);
    (void)REG_IME;
    REG_IME = ime;
}

// func_0208e138 (0x0208e138): sets the global allocator
ARM void func_0208e138(void *allocator) {
    data_021770a4 = (Gz::Memory::GzAllocator *)allocator;
}

// func_0208e148 (0x0208e148): allocates from the global allocator (alignment 4)
ARM void *func_0208e148(u32 size) {
    return Gz_Memory_GzAllocator_alloc_08e0b0(data_021770a4, size);
}

// EL_GetGlobalAdr (0x0208e164): allocates from the global allocator with the given alignment
ARM void *EL_GetGlobalAdr(u32 offset, u32 size) {
    return Gz_Memory_GzAllocator_alloc_08e0e0(data_021770a4, offset, size);
}

// func_0208e188 (0x0208e188): frees a block through the global allocator; declared in functions.h
ARM void func_0208e188(void *block) {
    Gz_Memory_GzAllocator_dealloc(data_021770a4, block);
}
