#include "engine/functions.h"

typedef struct TransferEntry {
    u32 size;
    u32 offset;
    void *data;
} TransferEntry;

extern "C" volatile u32 data_0217d250[];
extern "C" volatile TransferEntry data_0217d260[][3];
extern "C" volatile u32 data_0217d2f0;
extern "C" volatile TransferEntry data_0217d2f4[];
extern "C" volatile u32 data_0217d1e8;
extern "C" volatile TransferEntry data_0217d1ec[];
extern "C" volatile u32 data_0217d21c;
extern "C" volatile TransferEntry data_0217d220[];

void subTaskSendBgChar(s16 index, void *data, u32 offset, u32 size) {
    volatile TransferEntry *entry;
    u32 count = data_0217d250[index];

    if (count <= 2) {
        entry = &data_0217d260[index][count];
        entry->size = size;
        entry->offset = offset;
        entry->data = data;
        data_0217d250[index] = data_0217d250[index] + 1;
    }
}

void subTaskSendObjChar(void *data, u32 offset, u32 size) {
    volatile u32 *counter = &data_0217d2f0;
    u32 count = *counter;
    volatile TransferEntry *entry;

    if (count <= 1) {
        entry = &data_0217d2f4[count];
        entry->size = size;
        entry->offset = offset;
        entry->data = data;
        *counter = *counter + 1;
    }
}

void subTaskSendBgPlt(void *data, u32 offset, u32 size) {
    volatile u32 *counter = &data_0217d1e8;
    u32 count = *counter;
    volatile TransferEntry *entry;

    if (count <= 3) {
        entry = &data_0217d1ec[count];
        entry->size = size;
        entry->offset = offset;
        entry->data = data;
        *counter = *counter + 1;
    }
}

void subTaskSendObjPlt(void *data, u32 offset, u32 size) {
    volatile u32 *counter = &data_0217d21c;
    u32 count = *counter;
    volatile TransferEntry *entry;

    if (count <= 3) {
        entry = &data_0217d220[count];
        entry->size = size;
        entry->offset = offset;
        entry->data = data;
        *counter = *counter + 1;
    }
}
