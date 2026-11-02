#ifndef WIP_F_LAYOUT_TAG_H
#define WIP_F_LAYOUT_TAG_H

// Declarations for the layout block dispatcher of implementer F (round 16). The helpers it calls are not named yet.

#include "engine/functions.h"
#include "types.h"

// Four-word block record passed by value to the layout helpers
typedef struct LayoutQuad {
    u32 word[4];
} LayoutQuad;

extern "C" {
s32 func_020b5524(void *arg1, void *arg3, LayoutQuad q);
s32 func_020b54d0(void *arg1, void *arg3, LayoutQuad q);
s32 func_020b547c(void *arg1, void *arg3, LayoutQuad q);
s32 func_020b5424(void *arg1, u32 first, void *arg3, LayoutQuad q);
s32 Layout_createByTag(void *unused, void *arg1, s32 tag, void *arg3, const LayoutQuad *q);
}

#endif
