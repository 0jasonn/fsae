#include "engine/sound/snd_seq.h"

// Inserts node immediately before before, or appends it when before is null.
extern "C" void func_020c1fa0(SndList *list, u8 *before, void *nodeArg) {
    typedef struct Link {
        u8 *previous;
        u8 *next;
    } Link;
    u8 *node = (u8 *)nodeArg;
    u16 stride;
    Link *beforeLink;
    Link *nodeLink;
    Link *previousLink;

    if (before == 0) {
        SndList_Append(list, node);
        return;
    }
    if (before == list->first) {
        SndList_Prepend(list, node);
        return;
    }
    stride = list->stride;
    beforeLink = (Link *)(before + stride);
    nodeLink = (Link *)(node + stride);
    previousLink = (Link *)(beforeLink->previous + stride);
    nodeLink->previous = beforeLink->previous;
    nodeLink->next = before;
    previousLink->next = node;
    *(u8 **)(before + list->stride) = node;
    list->count++;
}
