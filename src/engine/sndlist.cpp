#include "engine/functions.h"
#include "global.h"
#include "engine/sndlist.h"

// Owner with a counted array of 12-byte entries at +0x20 (the first word of a free entry is -1).
typedef struct SndListOwner {
    /* 00 */ u8 unk_00[0x1c];
    /* 1c */ s32 entryCount;
    /* 20 */ u8 entries[0x20];
} SndListOwner;

// SndList_GetEntryCount: the number of entries of the owner.
extern "C" s32 SndList_GetEntryCount(void *owner);
ARM s32 SndList_GetEntryCount(void *owner) {
    return ((SndListOwner *)owner)->entryCount;
}

// SndList_GetEntry: returns entry index of the owner, or 0 when the index is out of range or the entry is free.
extern "C" void *SndList_GetEntry(void *owner, s32 index);
ARM void *SndList_GetEntry(void *owner, s32 index) {
    SndListOwner *list;
    u8 *entry;

    list = (SndListOwner *)owner;
    if (index < 0) {
        return 0;
    }
    if ((u32)index >= (u32)list->entryCount) {
        return 0;
    }
    entry = list->entries + index * 12;
    if (*(s32 *)entry == -1) {
        return 0;
    }
    return entry;
}

// SndList_Clear: clears the list.
extern "C" void SndList_Clear(SndList *list);
ARM void SndList_Clear(SndList *list) {
    list->last = 0;
    list->first = 0;
    list->capacity = 0;
    *(u32 *)&list->count = 0;
}

// SndList_Setup: sets the list up with the given last node and capacity. The first node is the position the list
// has before the fields are written.
extern "C" void SndList_Setup(SndList *list, u8 *last, u32 capacity);
ARM void SndList_Setup(SndList *list, u8 *last, u32 capacity) {
    list->first = SndList_GetCurrent(list);
    list->last = last;
    list->capacity = capacity;
    *(u32 *)&list->count = 0;
}

// SndList_GetCurrent: the node at the list's current position: last when the count has reached the capacity, otherwise the
// first node advanced by count / capacity of the span from first to last.
extern "C" u8 *SndList_GetCurrent(SndList *list);
ARM u8 *SndList_GetCurrent(SndList *list) {
    s32 count;
    s32 capacity;
    u8 *first;

    capacity = (s32)list->capacity;
    count = *(s32 *)&list->count;
    if (count >= capacity) {
        return list->last;
    }
    first = list->first;
    return first + (count * ((s32)list->last - (s32)first)) / capacity;
}

// SndList_Advance: advances the count when it is below the capacity.
extern "C" void SndList_Advance(SndList *list);
ARM void SndList_Advance(SndList *list) {
    s32 count;

    count = *(s32 *)&list->count;
    if (count < (s32)list->capacity) {
        *(s32 *)&list->count = count + 1;
    }
}

// SndList_IsFull: returns 1 when the count has reached the capacity.
extern "C" s32 SndList_IsFull(SndList *list);
ARM s32 SndList_IsFull(SndList *list) {
    return *(s32 *)&list->count >= (s32)list->capacity;
}

// SndList_Init: empties the list and sets its node stride.
extern "C" void SndList_Init(SndList *list, s32 stride);
ARM void SndList_Init(SndList *list, s32 stride) {
    list->first = 0;
    list->last = 0;
    list->count = 0;
    list->stride = (u16)stride;
}

// SndList_AddFirst: adds the first node. Its link words (at the stride) are cleared.
extern "C" void SndList_AddFirst(SndList *list, u8 *node);
ARM void SndList_AddFirst(SndList *list, u8 *node) {
    u16 stride;
    u16 count;

    stride = list->stride;
    *(s32 *)(node + stride + 4) = 0;
    *(s32 *)(node + stride) = 0;
    count = list->count;
    list->first = node;
    list->last = node;
    list->count = count + 1;
}

// SndList_Append: appends a node after the last one (the first node when the list is empty).
extern "C" void SndList_Append(SndList *list, u8 *node);
ARM void SndList_Append(SndList *list, u8 *node) {
    u16 stride;
    u8 *last;
    u16 count;

    if (list->first == 0) {
        SndList_AddFirst(list, node);
        return;
    }
    stride = list->stride;
    last = list->last;
    *(u8 **)(node + stride) = last;
    *(s32 *)(node + stride + 4) = 0;
    *(u8 **)(list->last + list->stride + 4) = node;
    count = list->count;
    list->last = node;
    list->count = count + 1;
}

// SndList_Prepend: puts a node before the first one (the first node when the list is empty).
extern "C" void SndList_Prepend(SndList *list, u8 *node);
ARM void SndList_Prepend(SndList *list, u8 *node) {
    u16 stride;
    u16 count;

    if (list->first == 0) {
        SndList_AddFirst(list, node);
        return;
    }
    stride = list->stride;
    *(s32 *)(node + stride) = 0;
    *(u8 **)(node + stride + 4) = list->first;
    *(u8 **)(list->first + list->stride) = node;
    count = list->count;
    list->first = node;
    list->count = count + 1;
}
