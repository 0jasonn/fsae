#ifndef SDK_OS_OS_MUTEX_H
#define SDK_OS_OS_MUTEX_H

// TwlSDK OS mutexes: a wait queue, the owner and a lock word; owned mutexes are linked into the owner's mutex queue.
#include "types.h"
#include "sdk/os/os_thread.h"

// lockWord: lock depth in the low 24 bits, lock kind in the top byte (0x10 = normal).
#define OS_MUTEX_SET_TYPE(word, type) (((word) & 0x00ffffff) | (type))
#define OS_MUTEX_SET_COUNT(word, count) (((word) & 0xff000000) | ((count) & 0x00ffffff))

typedef struct OsMutex {
    OsThreadQueue queue;  // 0x00: threads waiting for the mutex
    OsThread *thread;     // 0x08: owner
    u32 lockWord;         // 0x0c
    struct OsMutex *next; // 0x10: link in the owner's mutex queue
    struct OsMutex *prev; // 0x14
} OsMutex;

extern "C" {
void OS_InitMutex(OsMutex *mutex);
void OS_LockMutexFromWToR(OsMutex *mutex);
void OS_UnlockMutex(OsMutex *mutex);
void OSi_UnlockAllMutex(OsThread *thread);
BOOL OS_TryLockMutex(OsMutex *mutex);
void OSi_EnqueueTail(OsThread *thread, OsMutex *mutex);
void OSi_DequeueItem(OsThread *thread, OsMutex *mutex);

// Not decompiled yet.
void OSi_UnlockMutexCore(OsMutex *mutex, u32 type); // OSi_UnlockMutexCore (rename pending in scratch/agentC2/renames.txt)
OsMutex *OSi_RemoveMutexLinkFromQueue(OsMutexQueue *queue);
}

#endif
