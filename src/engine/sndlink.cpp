#include "engine/functions.h"
#include "global.h"
#include "engine/sndlink.h"

// func_020c2004: unlinks the node from the list (the first, last and neighbour links and the count) and clears its own
// link words. Kept under its plain name because the sound entry code calls it by that name.
extern "C" void func_020c2004(void *list, void *node);
ARM void func_020c2004(void *list, void *node) {
    SndList *owner;
    SndLink *link;
    u8 *prev;
    u8 *next;

    owner = (SndList *)list;
    link = (SndLink *)((u8 *)node + owner->stride);
    prev = link->prev;
    if (prev == 0) {
        owner->first = link->next;
    } else {
        ((SndLink *)(prev + owner->stride))->next = link->next;
    }
    next = link->next;
    if (next == 0) {
        owner->last = link->prev;
    } else {
        ((SndLink *)(next + owner->stride))->prev = link->prev;
    }
    link->prev = 0;
    link->next = 0;
    owner->count = owner->count - 1;
}

// func_020c2064: the node after node, or the first node when node is null.
extern "C" u8 *func_020c2064(SndList *list, u8 *node);
ARM u8 *func_020c2064(SndList *list, u8 *node) {
    if (node == 0) {
        return list->first;
    }
    return ((SndLink *)(node + list->stride))->next;
}

// SndList_GetPrev: the node before node, or the last node when node is null.
extern "C" u8 *SndList_GetPrev(SndList *list, u8 *node);
ARM u8 *SndList_GetPrev(SndList *list, u8 *node) {
    if (node == 0) {
        return list->last;
    }
    return ((SndLink *)(node + list->stride))->prev;
}
