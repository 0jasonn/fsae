#ifndef WIP_D_OWN_DECLS_H
#define WIP_D_OWN_DECLS_H

// Declarations for the D units that functions.h does not have yet (signatures from the callers; see the report).

#include "engine/entity.h"

extern "C" s32 AddHeart(Entity *e, s32 amount); // original name AddHeart, unmangled

#endif
