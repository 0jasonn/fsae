#ifndef SDK_OS_OS_MESSAGE_H
#define SDK_OS_OS_MESSAGE_H

// TwlSDK OS message queues: a ring of message pointers with send and receive wait queues.
#include "types.h"
#include "sdk/os/os_thread.h"

typedef struct OsMessageQueue {
    OsThreadQueue queueSend;    // 0x00
    OsThreadQueue queueReceive; // 0x08
    void **messages;            // 0x10
    s32 messageCount;           // 0x14
    s32 firstIndex;             // 0x18
    s32 usedCount;              // 0x1c
} OsMessageQueue;

extern "C" {
void OS_InitMessageQueue(OsMessageQueue *queue, void **messages, s32 count);
BOOL OS_SendMessage(OsMessageQueue *queue, void *message, s32 flags);
BOOL OS_ReceiveMessage(OsMessageQueue *queue, void **message, s32 flags);
BOOL OS_JamMessage(OsMessageQueue *queue, void *message, s32 flags);
}

#endif
