#ifndef WIP_G_SNDLIST_H
#define WIP_G_SNDLIST_H

#include "engine/functions.h"
#include "global.h"

// Intrusive list header (provisional layout). count is a halfword in the add functions and a word in
// SndList_Advance, so it is accessed with both widths. stride (halfword at +0xa) is the offset of the link words
// inside each node.
typedef struct SndList {
    /* 00 */ u8 *first;
    /* 04 */ u8 *last;
    /* 08 */ u16 count;
    /* 0a */ u16 stride;
    /* 0c */ u32 capacity;
} SndList;

extern "C" void *SndList_GetEntry(void *owner, s32 index);
extern "C" s32 SndList_GetEntryCount(void *owner);
extern "C" void SndList_Clear(SndList *list);
extern "C" void SndList_Setup(SndList *list, u8 *last, u32 capacity);
extern "C" u8 *SndList_GetCurrent(SndList *list);
extern "C" void SndList_Advance(SndList *list);
extern "C" s32 SndList_IsFull(SndList *list);
extern "C" void SndList_Init(SndList *list, s32 stride);
extern "C" void SndList_AddFirst(SndList *list, u8 *node);
extern "C" void SndList_Append(SndList *list, u8 *node);
extern "C" void SndList_Prepend(SndList *list, u8 *node);

#endif
