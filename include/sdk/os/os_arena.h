#ifndef SDK_OS_OS_ARENA_H
#define SDK_OS_OS_ARENA_H

// TwlSDK OS arenas and heaps. Arena ids 0-6 (main, main-ex, ITCM, DTCM, shared, WRAM...); the arena bounds are kept
// in the shared area at 0x02fffda0 (lo) and 0x02fffdc4 (hi), one word per arena.
// Heap bookkeeping: free and allocated blocks are doubly linked lists of OsHeapCell, 0x20-byte aligned; the cell header
// (prev, next, size) sits in the 0x20 bytes before the returned pointer.
#include "types.h"

typedef struct OsHeapCell {
    struct OsHeapCell *prev;
    struct OsHeapCell *next;
    s32 size;
} OsHeapCell;

typedef struct OsHeapDesc {
    s32 size;
    OsHeapCell *free;
    OsHeapCell *allocated;
} OsHeapDesc;

typedef struct OsHeapInfo {
    s32 currentHeap;
    u8 unk_04[0xc];
    OsHeapDesc *heaps;
} OsHeapInfo;

extern OsHeapInfo *data_02129b9c[9]; // heap info per arena (0x24 bytes)

extern "C" {
void *OS_GetArenaHi(s32 id);
void *OS_GetArenaLo(s32 id);
void OS_SetArenaHi(s32 id, void *hi);
void OS_SetArenaLo(s32 id, void *lo);
void *OS_AllocFromArenaLo(s32 id, u32 size, u32 align);
OsHeapCell *DLAddFront(OsHeapCell *list, OsHeapCell *cell);
OsHeapCell *DLExtract(OsHeapCell *list, OsHeapCell *cell);
OsHeapCell *DLInsert(OsHeapCell *list, OsHeapCell *cell);
void *OS_AllocFromHeap(s32 id, s32 heap, u32 size);
void OS_FreeToHeap(s32 id, s32 heap, void *ptr);
BOOL OS_IsOnExtendedMainMemory(const void *address);
BOOL OS_IsOnVram(const void *address);
}

#endif
