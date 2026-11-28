#ifndef KNIFE_APP_KNIFE_FILE_2_H
#define KNIFE_APP_KNIFE_FILE_2_H

#include "types.h"
#include "sdk/snd/snd_command.h"  // TwlSDK SND command API (and OS_InitMutex)
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_api.h"
#include "sdk/os/os_event.h"
#include "sdk/os/os_mutex.h"
#include "sdk/os/os_thread.h"

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

    FSFile fsFile;      // 0x0c: FS file handle
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
    OsEvent event;      // 0x1c
    OsMutex mutex;      // 0x28
    OsThread thread;    // 0x40
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
void *func_0208e148(u32 size);
// OS_CreateThread, OS_WakeupThreadDirect, OS_ExitThread, OS_YieldThread: sdk/os/os_thread.h.
s32 Obj_GetField70(void *thread);
void Stub_EmptyC(void);
Knife::File::Entity *Knife_File_Entity_ctor(Knife::File::Entity *self, const char *name);
u32 Knife_File_Entity_getField54(Knife::File::Entity *self);
u8 Knife_File_Entity_isReadDone(Knife::File::Entity *self);
extern char data_0211abcc[]; // vtable the List dtors leave behind
extern Knife::File::System data_02172138;
extern Knife::File::FileTable data_02176238;
extern Knife::File::Entity *data_02176278[16];
extern Knife::File::SlotInfo data_021762b8[16];
}

#endif
