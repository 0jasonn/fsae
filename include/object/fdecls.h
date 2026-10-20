#ifndef WIP_F_FDECLS_H
#define WIP_F_FDECLS_H

// Prototypes shared by the F units (name plate, bar master, option panels) that engine/functions.h does not have yet.
// ObjAnimMoveLine returns nonzero when its animation has ended (the caller tests r0; objdecls_d.h has it as void).

#include "engine/functions.h"

extern "C" void MI_UncompressLZ16(const void *src, void *dst);

// Option panel helper at 0x0205c770 (star_adjust). Moves the entity's sprite by (a, b) in steps.
void star_adjust(Entity *e, s16 a, s16 b);

#endif
