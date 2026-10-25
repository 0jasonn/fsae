#ifndef WIP_D_KNIFE_FILE_2_H
#define WIP_D_KNIFE_FILE_2_H

#include "types.h"

namespace Knife {
namespace File {

class Entity;

// Knife::File::List: the vtable and the links of the circular list of Entities (Entity derives from it)
class List {
public:
    virtual void virtualDtor(void); // vtable slot 0; the body is not written here
    List *next;                     // 0x04
    List *prev;                     // 0x08
};

// Knife::File::Entity (0xa0 bytes): a list node that reads one file from the archive
class Entity : public List {
public:
    BOOL read(void);

    u8 fsFile[0x48];    // 0x0c: FS file handle
    u32 buffer;         // 0x54: block the file is read into
    u32 fileSize;       // 0x58
    u8 path[0x40];      // 0x5c: archive path, written by the constructor
    u8 readDone;        // 0x9c
};

// Knife::File::System (data_02172138): the loader state. queue is the sentinel of the list of entities waiting to be
// read. The thread stack (0x4000 bytes) follows the thread object and ends at data_02176238.
class System {
public:
    static void threadFunction(void *arg);
    static void initialize(u32 flags);
    static void yieldThread(void);
    static Entity *alloc(const char *name);
    static void release(Entity *entity);
    static void allocGroup(u16 group);

    s32 quitRequested;  // 0x00
    u8 unk_04[0x0c];
    List queue;         // 0x10
    u8 event[0x0c];     // 0x1c: OSEvent
    u8 mutex[0x18];     // 0x28: OSMutex
    u8 thread[0xc0];    // 0x40: OSThread
};

// One record of the file table, 0x30 bytes each: valid flag at 0x14, file name at 0x15
class FileRecord {
public:
    u8 unk_00[0x14];
    u8 valid;
    char name[0x1b];
};

// data_02176238: the file table; the record array is at 0x1c
class FileTable {
public:
    u8 unk_00[0x1c];
    FileRecord *records;
};

// data_021762b8: one 8-byte entry per wave slot. waveData is the registered wave data (NULL when free). The word at
// 0x04 has the registered flag in bits 0-7 and the lock flag in bits 8-15 (both signed bytes).
class SlotInfo {
public:
    void *waveData;     // 0x00
    s32 registered : 8; // 0x04 bits 0-7
    s32 lockFlag : 8;   // 0x04 bits 8-15
    u32 unk_04 : 16;    // 0x04 bits 16-31
};

}
}

extern "C" {
// TwlSDK and engine calls used by the Knife file loader (dsd names where the library name is not known)
void FS_Init(void);
BOOL FS_FindDir(void *file, void *path);
u32 FS_GetFileLength(void *file);
u32 FS_ReadFileAsync(void *file, void *dst, u32 size);
BOOL FS_WaitAsync(void *file);
void FS_CloseFile(void *file);
void FS_InitFile(void *file);
u32 WBT_SetPacketSize(s32 a, s32 b);
void *func_0208e148(u32 size);
void OS_InitMutex(void *mutex);
void OS_InitEvent(void *event);
void OS_LockMutexFromWToR(void *mutex);
void OS_UnlockMutex(void *mutex);
void OS_SignalEvent(void *event, s32 value);
void OS_ClearEvent(void *event, s32 value);
void Os_WaitEventExWrap(void *event, s32 timeout, s32 flags);
void OS_CreateThread(void *thread, void (*entry)(void *), void *arg, void *stackTop, u32 stackSize, s32 priority);
void OS_WakeupThreadDirect(void *thread);
void OS_ExitThread(void);
void OS_YieldThread(void);
s32 Obj_GetField70(void *thread);
void func_02017c34(void);
Knife::File::Entity *Knife_File_Entity_ctor(Knife::File::Entity *self, const char *name);
u32 Knife_File_Entity_getField54(Knife::File::Entity *self);
u8 Knife_File_Entity_isReadDone(Knife::File::Entity *self);
extern char data_0211abcc[]; // vtable the List dtors leave behind
extern Knife::File::System data_02172138;
extern Knife::File::FileTable data_02176238;
extern Knife::File::Entity *data_02176278[16];
extern Knife::File::SlotInfo data_021762b8[16];
extern u32 data_02129938[]; // word 1 holds the main OSThread pointer
}

#endif
