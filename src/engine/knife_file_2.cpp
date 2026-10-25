#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/knife_file_2.h"

// Knife::File::Entity::read, the List dtors and the Knife::File::System loader, 0x0208c7ac to 0x0208cb74.
// Provisional names in scratch/agentD/renames.txt: Knife_File_System_yieldThread -> Knife_File_System_yieldThread,
// Knife_File_System_allocGroup -> Knife_File_System_allocGroup. func_0208cb74 keeps its name because functions.h declares it.
// The List dtors stay plain extern "C" functions: their D0/D1 mangled names cannot be resolved to symbols.txt yet.

namespace Knife {
namespace File {

// Entity::read (0x0208c7ac): if the path exists, reads the whole file into a block from EL_GetGlobalAdr. readDone is
// set either way. Returns whether the read finished.
ARM BOOL Entity::read(void) {
    BOOL ok = FALSE;

    if (FS_FindDir(fsFile, path) != FALSE) {
        fileSize = FS_GetFileLength(fsFile);
        buffer = (u32)EL_GetGlobalAdr(fileSize, 0x20);
        if (buffer != 0) {
            if (FS_ReadFileAsync(fsFile, (void *)buffer, fileSize) == fileSize) {
                if (FS_WaitAsync(fsFile) != FALSE) {
                    ok = TRUE;
                }
            }
        }
        FS_CloseFile(fsFile);
    }
    readDone = 1;
    return ok;
}

}
}

// List::~List, deleting dtor (0x0208c82c): unlinks the node, leaves the List vtable and frees it
extern "C" Knife::File::List *Knife_File_List_dtor_List_08c82c(Knife::File::List *self);
ARM Knife::File::List *Knife_File_List_dtor_List_08c82c(Knife::File::List *self) {
    *(void **)self = data_0211abcc;
    self->next->prev = self->prev;
    self->prev->next = self->next;
    self->prev = self;
    self->next = self;
    operator delete(self);
    return self;
}

// List::~List, base dtor (0x0208c868): unlinks the node and leaves the List vtable
extern "C" void Knife_File_List_dtor_List_08c868(Knife::File::List *self);
ARM void Knife_File_List_dtor_List_08c868(Knife::File::List *self) {
    *(void **)self = data_0211abcc;
    self->next->prev = self->prev;
    self->prev->next = self->next;
    self->prev = self;
    self->next = self;
}

namespace Knife {
namespace File {

// System::threadFunction (0x0208c894): the loader thread. Waits until an entity is queued, takes the first one off the
// queue, reads it and yields, until quitRequested is set. Then the thread exits.
ARM void System::threadFunction(void *arg) {
    Entity *entity;
    BOOL empty;

    if (data_02172138.quitRequested == 0) {
        do {
            for (;;) {
                OS_LockMutexFromWToR(data_02172138.mutex);
                empty = (List *)&data_02172138.queue == data_02172138.queue.next;
                OS_UnlockMutex(data_02172138.mutex);
                if (!empty) {
                    break;
                }
                Os_WaitEventExWrap(data_02172138.event, 1, 0);
                OS_ClearEvent(data_02172138.event, 1);
            }
            OS_LockMutexFromWToR(data_02172138.mutex);
            entity = (Entity *)data_02172138.queue.next;
            entity->next->prev = entity->prev;
            entity->prev->next = entity->next;
            entity->prev = entity;
            entity->next = entity;
            OS_UnlockMutex(data_02172138.mutex);
            entity->read();
            yieldThread();
        } while (data_02172138.quitRequested == 0);
    }
    OS_ExitThread();
}

// System::initialize (0x0208c968): clears the quit flag, sets up the file system and the archive tables, enables the
// IRQ mask for flags, and starts the loader thread
ARM void System::initialize(u32 flags) {
    s32 tableSize;
    void *tableBuf;

    data_02172138.quitRequested = 0;
    FS_Init();
    tableSize = WBT_SetPacketSize(0, 0);
    tableBuf = func_0208e148(tableSize);
    WBT_SetPacketSize((s32)tableBuf, tableSize);
    OS_EnableIrqMask((flags & 0x10 ? 0x10000000 : 0x100) << (flags & 3));
    OS_InitMutex(data_02172138.mutex);
    OS_InitEvent(data_02172138.event);
    OS_CreateThread(data_02172138.thread, System::threadFunction, 0, &data_02176238, 0x4000,
                    Obj_GetField70((void *)data_02129938[1]));
    OS_WakeupThreadDirect(data_02172138.thread);
    func_02017c34();
}

// System::yieldThread (0x0208ca28): tail call to OS_YieldThread
ARM void System::yieldThread(void) {
    ((void (*)(void))OS_YieldThread)();
}

// System::alloc (0x0208ca34): news an Entity (0xa0 bytes) for the name and appends it to the queue. The loader thread
// is signalled when the queue was empty.
ARM Entity *System::alloc(const char *name) {
    Entity *entity;
    BOOL wasEmpty;

    entity = (Entity *)func_0208e148(0xa0);
    if (entity != NULL) {
        entity = Knife_File_Entity_ctor(entity, name);
    }
    OS_LockMutexFromWToR(data_02172138.mutex);
    wasEmpty = (List *)&data_02172138.queue == data_02172138.queue.next;
    entity->next = data_02172138.queue.prev->next;
    entity->prev = data_02172138.queue.prev;
    data_02172138.queue.prev->next = entity;
    data_02172138.queue.prev = entity;
    if (wasEmpty) {
        OS_SignalEvent(data_02172138.event, 1);
    }
    OS_UnlockMutex(data_02172138.mutex);
    return entity;
}

// System::release (0x0208cad0): destroys an entity through its vtable (slot 0) and frees it
ARM void System::release(Entity *entity) {
    if (entity != NULL) {
        entity->virtualDtor();
        func_0208e188(entity);
    }
}

// System::allocGroup (0x0208caf4, provisional name): for the two slots of a group, allocates an entity for each valid
// record whose slot is empty
ARM void System::allocGroup(u16 group) {
    u16 i;
    u16 index;
    FileRecord *record;

    for (i = 0; i < 2; i++) {
        index = (u16)(i + group * 2);
        record = &data_02176238.records[index];
        if (record->valid != 0) {
            if (data_021762b8[index].waveData == NULL && data_02176278[index] == NULL) {
                data_02176278[index] = alloc(record->name);
            }
        }
    }
}

}
}

// func_0208cb74 (0x0208cb74): the group ID starts at 0x1ea; declared in functions.h
ARM void func_0208cb74(u16 id) {
    ((void (*)(u16))Knife::File::System::allocGroup)((u16)(id - 0x1ea));
}

// m4aLockWaveData (0x0208cb94): sets the lock flag of the second slot of the pair and copies it to the first
ARM void m4aLockWaveData(u16 id) {
    int first;
    Knife::File::SlotInfo *a;
    Knife::File::SlotInfo *b;

    first = (id - 0x1ea) * 2;
    a = &data_021762b8[first];
    b = &data_021762b8[first + 1];
    b->lockFlag = 1;
    a->lockFlag = b->lockFlag;
}

// m4aUnlockWaveData (0x0208cbe8): clears the lock flag of the pair, as m4aLockWaveData sets it
ARM void m4aUnlockWaveData(u16 id) {
    int first;
    Knife::File::SlotInfo *a;
    Knife::File::SlotInfo *b;

    first = (id - 0x1ea) * 2;
    a = &data_021762b8[first];
    b = &data_021762b8[first + 1];
    b->lockFlag = 0;
    a->lockFlag = b->lockFlag;
}

// m4aRegistWaveData (0x0208cc38): stores the wave data in slot 2 * index + which and marks it registered
extern "C" void m4aRegistWaveData(s32 index, s32 which, const void *waveData);
ARM void m4aRegistWaveData(s32 index, s32 which, const void *waveData) {
    Knife::File::SlotInfo *slot;

    slot = &data_021762b8[which + index * 2];
    slot->waveData = (void *)waveData;
    slot->registered = 1;
}

// m4aReleaseWaveData (0x0208cc60): frees the wave data of slot 2 * index + which, unless the slot is locked or still
// registered, and only when its file record is valid
extern "C" void m4aReleaseWaveData(s32 index, s32 which);
ARM void m4aReleaseWaveData(s32 index, s32 which) {
    s32 slot;

    slot = which + index * 2;
    if (data_02176238.records[slot].valid == 0) {
        return;
    }
    if (data_021762b8[slot].waveData == NULL) {
        return;
    }
    if (data_021762b8[slot].lockFlag != 0) {
        return;
    }
    if (data_021762b8[slot].registered != 0) {
        return;
    }
    func_0208e188(data_021762b8[slot].waveData);
    data_021762b8[slot].waveData = NULL;
}
