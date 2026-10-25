#ifndef WIP_G_SNDLINK_H
#define WIP_G_SNDLINK_H

#include "engine/functions.h"
#include "global.h"
#include "engine/sndlist.h"

// Link words of a node in an intrusive SndList: they sit at node + list->stride (prev at +0, next at +4).
typedef struct SndLink {
    u8 *prev;
    u8 *next;
} SndLink;

extern "C" void func_020c2004(void *list, void *node);
extern "C" u8 *func_020c2064(SndList *list, u8 *node);
extern "C" u8 *SndList_GetPrev(SndList *list, u8 *node);

#endif
