#include "global.h"
#include "types.h"
#include "sdk/os/os_arena.h"
#include "sdk/os/os_interrupts.h"

void OS_SetArenaHi(s32 id, void *hi) {
    ((void **)0x02fffdc4)[id] = hi;
}

void OS_SetArenaLo(s32 id, void *lo) {
    ((void **)0x02fffda0)[id] = lo;
}

// Takes size bytes (rounded up to align) from the low end of arena id; returns NULL if the arena is unset or too small.
void *OS_AllocFromArenaLo(s32 id, u32 size, u32 align) {
    u32 lo = (u32)OS_GetArenaLo(id);
    u32 start;
    u32 end;
    if (lo == 0) {
        return NULL;
    }
    start = (lo + align - 1) & ~(align - 1);
    end = start + size;
    end = (end + align - 1) & ~(align - 1);
    if (end > (u32)OS_GetArenaHi(id)) {
        return NULL;
    }
    OS_SetArenaLo(id, (void *)end);
    return (void *)start;
}

// Pushes cell onto the front of the doubly linked list and returns the new head.
OsHeapCell *DLAddFront(OsHeapCell *list, OsHeapCell *cell) {
    cell->next = list;
    cell->prev = NULL;
    if (list != NULL) {
        list->prev = cell;
    }
    return cell;
}

// Unlinks cell from list and returns the (possibly new) head.
OsHeapCell *DLExtract(OsHeapCell *list, OsHeapCell *cell) {
    if (cell->next != NULL) {
        cell->next->prev = cell->prev;
    }
    if (cell->prev == NULL) {
        list = cell->next;
    } else {
        cell->prev->next = cell->next;
    }
    return list;
}

// Inserts cell into the address-sorted list, merging it with neighbours it touches. Returns the head.
OsHeapCell *DLInsert(OsHeapCell *list, OsHeapCell *cell) {
    OsHeapCell *prev = NULL;
    OsHeapCell *next = list;

    for (; next != NULL; prev = next, next = next->next) {
        if (cell <= next) {
            break;
        }
    }
    cell->next = next;
    cell->prev = prev;
    if (next != NULL) {
        next->prev = cell;
        if ((u8 *)cell + cell->size == (u8 *)next) {
            cell->size += next->size;
            next = next->next;
            cell->next = next;
            if (next != NULL) {
                next->prev = cell;
            }
        }
    }
    if (prev != NULL) {
        prev->next = cell;
        if ((u8 *)prev + prev->size == (u8 *)cell) {
            prev->size += cell->size;
            prev->next = next;
            if (next != NULL) {
                next->prev = prev;
            }
        }
        return list;
    }
    return cell;
}

// First-fit allocation from heap (negative = the current heap) of arena id; the block gets a 0x20-byte header.
void *OS_AllocFromHeap(s32 id, s32 heap, u32 size) {
    OsHeapInfo *info;
    OsHeapDesc *desc;
    OsHeapCell *cell;
    OsHeapCell *rest;
    u32 state;
    u32 leftover;

    state = OS_DisableInterrupts();
    info = data_02129b9c[id];
    if (info == NULL) {
        OS_RestoreInterrupts(state);
        return NULL;
    }
    if (heap < 0) {
        heap = info->currentHeap;
    }
    desc = &info->heaps[heap];
    size = (size + 0x3f) & ~0x1f;
    for (cell = desc->free; cell != NULL; cell = cell->next) {
        if ((s32)size <= cell->size) {
            break;
        }
    }
    if (cell == NULL) {
        OS_RestoreInterrupts(state);
        return NULL;
    }
    leftover = cell->size - size;
    if (leftover < 0x40) {
        desc->free = DLExtract(desc->free, cell);
    } else {
        cell->size = size;
        rest = (OsHeapCell *)((u8 *)cell + size);
        rest->size = leftover;
        rest->prev = cell->prev;
        rest->next = cell->next;
        if (rest->next != NULL) {
            rest->next->prev = rest;
        }
        if (rest->prev != NULL) {
            rest->prev->next = rest;
        } else {
            desc->free = rest;
        }
    }
    desc->allocated = DLAddFront(desc->allocated, cell);
    OS_RestoreInterrupts(state);
    return (u8 *)cell + 0x20;
}

// Returns a block from OS_AllocFromHeap to the free list of its heap.
void OS_FreeToHeap(s32 id, s32 heap, void *ptr) {
    OsHeapInfo *info;
    OsHeapDesc *desc;
    OsHeapCell *cell;
    u32 state;

    state = OS_DisableInterrupts();
    info = data_02129b9c[id];
    if (heap < 0) {
        heap = info->currentHeap;
    }
    desc = &info->heaps[heap];
    cell = (OsHeapCell *)((u8 *)ptr - 0x20);
    desc->allocated = DLExtract(desc->allocated, cell);
    desc->free = DLInsert(desc->free, cell);
    OS_RestoreInterrupts(state);
}

BOOL OS_IsOnExtendedMainMemory(const void *address) {
    if ((u32)address >= 0x0d000000) {
        if ((u32)address < 0x0e000000) {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL OS_IsOnVram(const void *address) {
    if ((u32)address >= 0x05000000) {
        if ((u32)address < 0x07000800) {
            return TRUE;
        }
    }
    return FALSE;
}
