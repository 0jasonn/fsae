#include "global.h"
#include "types.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/os/os_irq.h"
#include "sdk/os/os_message.h"
#include "sdk/os/os_mutex.h"
#include "sdk/os/os_thread.h"

void OS_InitMessageQueue(OsMessageQueue *queue, void **messages, s32 count) {
    queue->queueSend.head = queue->queueSend.tail = NULL;
    queue->queueReceive.head = queue->queueReceive.tail = NULL;
    queue->messages = messages;
    queue->messageCount = count;
    queue->firstIndex = 0;
    queue->usedCount = 0;
}

BOOL OS_SendMessage(OsMessageQueue *queue, void *message, s32 flags) {
    u32 state = OS_DisableInterrupts();
    while (queue->messageCount <= queue->usedCount) {
        if ((flags & 1) == 0) {
            OS_RestoreInterrupts(state);
            return FALSE;
        }
        Os_LinkThreadAndFlush(&queue->queueSend);
    }
    queue->messages[(queue->firstIndex + queue->usedCount) % queue->messageCount] = message;
    queue->usedCount++;
    OS_WakeupThread(&queue->queueReceive);
    OS_RestoreInterrupts(state);
    return TRUE;
}

BOOL OS_ReceiveMessage(OsMessageQueue *queue, void **message, s32 flags) {
    u32 state = OS_DisableInterrupts();
    while (queue->usedCount == 0) {
        if ((flags & 1) == 0) {
            OS_RestoreInterrupts(state);
            return FALSE;
        }
        Os_LinkThreadAndFlush(&queue->queueReceive);
    }
    if (message != NULL) {
        *message = queue->messages[queue->firstIndex];
    }
    queue->firstIndex = (queue->firstIndex + 1) % queue->messageCount;
    queue->usedCount--;
    OS_WakeupThread(&queue->queueSend);
    OS_RestoreInterrupts(state);
    return TRUE;
}

BOOL OS_JamMessage(OsMessageQueue *queue, void *message, s32 flags) {
    u32 state = OS_DisableInterrupts();
    while (queue->messageCount <= queue->usedCount) {
        if ((flags & 1) == 0) {
            OS_RestoreInterrupts(state);
            return FALSE;
        }
        Os_LinkThreadAndFlush(&queue->queueSend);
    }
    queue->firstIndex = (queue->firstIndex + queue->messageCount - 1) % queue->messageCount;
    queue->messages[queue->firstIndex] = message;
    queue->usedCount++;
    OS_WakeupThread(&queue->queueReceive);
    OS_RestoreInterrupts(state);
    return TRUE;
}

void OS_InitMutex(OsMutex *mutex) {
    mutex->queue.head = mutex->queue.tail = NULL;
    mutex->thread = NULL;
    mutex->lockWord = OS_MUTEX_SET_COUNT(mutex->lockWord, 0);
    mutex->lockWord = OS_MUTEX_SET_TYPE(mutex->lockWord, 0);
}

void OS_LockMutexFromWToR(OsMutex *mutex) {
    u32 state = OS_DisableInterrupts();
    OsThread *current = data_02129938.current;
    for (;;) {
        if (OS_TryLockMutex(mutex)) {
            break;
        }
        current->blockedOn = mutex;
        Os_LinkThreadAndFlush(&mutex->queue);
        current->blockedOn = NULL;
    }
    OS_RestoreInterrupts(state);
}

void OS_UnlockMutex(OsMutex *mutex) {
    OSi_UnlockMutexCore(mutex, 0x10000000);
}

void OSi_UnlockAllMutex(OsThread *thread) {
    OsMutex *mutex;
    while (thread->mutexQueue.head != NULL) {
        mutex = OSi_RemoveMutexLinkFromQueue(&thread->mutexQueue);
        mutex->lockWord = OS_MUTEX_SET_COUNT(mutex->lockWord, 0);
        mutex->thread = NULL;
        mutex->lockWord = OS_MUTEX_SET_TYPE(mutex->lockWord, 0);
        OS_WakeupThread(&mutex->queue);
    }
}

BOOL OS_TryLockMutex(OsMutex *mutex) {
    u32 state = OS_DisableInterrupts();
    OsThread *current = data_02129938.current;
    BOOL locked;
    if (mutex->thread == NULL) {
        u32 word = OS_MUTEX_SET_TYPE(mutex->lockWord, 0x10000000);
        mutex->thread = current;
        mutex->lockWord = OS_MUTEX_SET_COUNT(word, word + 1);
        OSi_EnqueueTail(current, mutex);
        locked = TRUE;
    } else if (mutex->thread == current) {
        mutex->lockWord = OS_MUTEX_SET_COUNT(mutex->lockWord, mutex->lockWord + 1);
        locked = TRUE;
    } else {
        locked = FALSE;
    }
    OS_RestoreInterrupts(state);
    return locked;
}
