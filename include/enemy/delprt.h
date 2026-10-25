#ifndef WIP_B_DELPRT_H
#define WIP_B_DELPRT_H

#include "engine/functions.h"

// Per-type flag word read by delprtInfo (flagBits, shared with other actors: index = Entity type2).
extern const u32 flagBits[];

void delprtInfo(Entity *e);

#endif
