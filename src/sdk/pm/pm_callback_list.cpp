#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/pm/pm.h"

// One entry of a PM callback list: callback(arg) is run in list order, entries are sorted by priority.
typedef struct PmCallbackNode {
    void (*callback)(void *arg); // 0x00
    void *arg;                   // 0x04
    s32 priority;                // 0x08
    struct PmCallbackNode *next; // 0x0c
} PmCallbackNode;

// PMi_InsertList(list, item, priority, prepend) (0x0201d56c): inserts item into the priority-sorted list; among equal
// priorities a prepend of 0 goes after the existing ones and 1 before them.
void PMi_InsertList(void **list, void *item, s32 priority, s32 prepend) {
    PmCallbackNode *node = (PmCallbackNode *)item;
    PmCallbackNode *current;
    PmCallbackNode *previous;
    u32 irq;

    if (list == NULL) {
        return;
    }
    node->priority = priority;
    irq = OS_DisableInterrupts();
    current = (PmCallbackNode *)*list;
    previous = NULL;
    while (current != NULL) {
        if (prepend == 0 && current->priority > priority) {
            break;
        }
        if (prepend == 1 && current->priority >= priority) {
            break;
        }
        previous = current;
        current = current->next;
    }
    if (current != NULL) {
        node->next = current;
    } else {
        node->next = NULL;
    }
    if (previous != NULL) {
        previous->next = node;
    } else {
        *list = node;
    }
    OS_RestoreInterrupts(irq);
}

// PMi_DeleteList(list, item) (0x0201d5f8): unlinks item from the list when present.
void PMi_DeleteList(void **list, void *item) {
    PmCallbackNode *node;
    PmCallbackNode *previous;
    u32 irq;

    if (list == NULL) {
        return;
    }
    irq = OS_DisableInterrupts();
    node = (PmCallbackNode *)*list;
    previous = node;
    while (node != NULL) {
        if (node == (PmCallbackNode *)item) {
            if (node == previous) {
                *list = node->next;
            } else {
                previous->next = node->next;
            }
            break;
        }
        previous = node;
        node = node->next;
    }
    OS_RestoreInterrupts(irq);
}

// PMi_ExecuteList(list) (0x0201d650): calls every callback of the list with its argument.
void PMi_ExecuteList(void *list) {
    PmCallbackNode *node = (PmCallbackNode *)list;

    if (node == NULL) {
        return;
    }
    do {
        node->callback(node->arg);
        node = node->next;
    } while (node != NULL);
}
