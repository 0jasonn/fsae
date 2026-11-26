#include "global.h"
#include "types.h"
#include "sdk/os/os_mutex.h"

// Appends mutex to the thread's list of owned mutexes.
void OSi_EnqueueTail(OsThread *thread, OsMutex *mutex) {
    OsMutex *tail = thread->mutexQueue.tail;
    if (tail == NULL) {
        thread->mutexQueue.head = mutex;
    } else {
        tail->next = mutex;
    }
    mutex->prev = tail;
    mutex->next = NULL;
    thread->mutexQueue.tail = mutex;
}

void OSi_DequeueItem(OsThread *thread, OsMutex *mutex) {
    OsMutex *next = mutex->next;
    OsMutex *prev = mutex->prev;
    if (next == NULL) {
        thread->mutexQueue.tail = prev;
    } else {
        next->prev = prev;
    }
    if (prev == NULL) {
        thread->mutexQueue.head = next;
    } else {
        prev->next = next;
    }
}
