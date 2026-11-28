#include "sdk/os/os_thread.h"
#include "sdk/os/os_mutex.h"

// Thread wait queues (sorted by priority, linked through the thread record) and the scheduler thread list.

void OSi_InsertLinkToQueue(OsThreadQueue *queue, OsThread *thread) {
    OsThread *cur = queue->head;
    while (cur != NULL && cur->priority <= thread->priority) {
        if (cur == thread) {
            return;
        }
        cur = cur->linkNext;
    }
    if (cur == NULL) {
        OsThread *tail = queue->tail;
        if (tail == NULL) {
            queue->head = thread;
        } else {
            tail->linkNext = thread;
        }
        thread->linkPrev = tail;
        thread->linkNext = NULL;
        queue->tail = thread;
    } else {
        OsThread *prev = cur->linkPrev;
        if (prev == NULL) {
            queue->head = thread;
        } else {
            prev->linkNext = thread;
        }
        thread->linkPrev = prev;
        thread->linkNext = cur;
        cur->linkPrev = thread;
    }
}

OsThread *OSi_RemoveLinkFromQueue(OsThreadQueue *queue) {
    OsThread *thread = queue->head;
    if (thread != NULL) {
        OsThread *next = thread->linkNext;
        queue->head = next;
        if (next != NULL) {
            next->linkPrev = NULL;
        } else {
            queue->tail = NULL;
            thread->link = NULL;
        }
    }
    return thread;
}

OsThread *OSi_RemoveSpecifiedLinkFromQueue(OsThreadQueue *queue, OsThread *thread) {
    OsThread *cur;
    OsThread *next;
    OsThread *head;
    OsThread *prev;
    head = queue->head;
    cur = head;
    while (cur != NULL) {
        next = cur->linkNext;
        if (cur == thread) {
            prev = cur->linkPrev;
            if (head == cur) {
                queue->head = next;
            } else {
                prev->linkNext = next;
            }
            if (queue->tail == cur) {
                queue->tail = prev;
            } else {
                next->linkPrev = prev;
            }
            break;
        }
        cur = next;
    }
    return cur;
}

OsMutex *OSi_RemoveMutexLinkFromQueue(OsMutexQueue *queue) {
    OsMutex *mutex = queue->head;
    if (mutex != NULL) {
        OsMutex *next = mutex->next;
        queue->head = next;
        if (next != NULL) {
            next->prev = NULL;
        } else {
            queue->tail = NULL;
        }
    }
    return mutex;
}

void OSi_InsertThreadToList(OsThread *thread) {
    OsThread *cur;
    OsThread *prev;
    OsThread *first;
    prev = NULL;
    first = data_0212991c.list;
    cur = first;
    while (cur != NULL && cur->priority < thread->priority) {
        prev = cur;
        cur = cur->next;
    }
    if (prev == NULL) {
        thread->next = first;
        data_0212991c.list = thread;
    } else {
        thread->next = prev->next;
        prev->next = thread;
    }
}

void OSi_RemoveThreadFromList(OsThread *thread) {
    OsThread *prev = NULL;
    OsThread *cur = data_0212991c.list;
    while (cur != NULL && cur != thread) {
        prev = cur;
        cur = cur->next;
    }
    if (prev == NULL) {
        data_0212991c.list = thread->next;
    } else {
        prev->next = thread->next;
    }
}
