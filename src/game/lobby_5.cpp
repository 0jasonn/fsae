#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/lobby.h"

// Functions in this file (no original names, provisional names from what they do):
//   lobby_msgObj_init (lobby_msgObj_init), lobby_msgObj_release (lobby_msgObj_release), lobby_freeBlock (lobby_freeBlock)
// lobby_releaseObj (lobby_releaseObj) is parked in scratch/agentF/nonmatching/lobby_releaseObj.cpp

extern "C" void lobby_releaseObj(void *heap, void *obj);
extern "C" void lobby_freeBlock(void *heap, void *block);

// lobby_msgObj_init(self) (0x020b4e60, provisional name): sets the vtable of the message object and clears its fields
extern "C" void lobby_msgObj_init(void *self);
ARM void lobby_msgObj_init(void *self) {
    u8 *obj;

    obj = (u8 *)self;
    *(void **)obj = data_02126a48;
    *(u32 *)(obj + 4) = 0;
    *(u16 *)(obj + 8) = 0;
    *(u16 *)(obj + 0xa) = 0;
    *(u16 *)(obj + 0x14) = 0;
    *(u32 *)(obj + 0x18) = 0;
    *(u16 *)(obj + 0x1c) = 0;
}

// lobby_msgObj_release(obj, heap) (0x020b4e8c, provisional name): releases the two blocks of a message object
extern "C" void lobby_msgObj_release(void *obj, void *heap);
ARM void lobby_msgObj_release(void *obj, void *heap) {
    lobby_releaseObj(heap, *(void **)((u8 *)obj + 4));
    lobby_freeBlock(heap, *(void **)((u8 *)obj + 0x18));
}

// lobby_freeBlock(heap, block) (0x020b4eb4, provisional name): frees the block when it is not NULL
ARM void lobby_freeBlock(void *heap, void *block) {
    if (block == NULL) {
        return;
    }
    Heap_VirtualFree(*(void **)heap, block);
}
