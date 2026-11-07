#ifndef WIP_K_K_DECLS_H
#define WIP_K_K_DECLS_H

#include "types.h"
#include "engine/entity.h"

// Prototypes of functions defined in src/wip/K (C++ linkage unless noted); the reviewer moves them to real headers.
void entry_check(void);
void set67_init(Entity *e);

extern "C" {
s32 nameEntryUIView_checkSpace(void *self);
}

#endif
