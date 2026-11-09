#ifndef WIP_A_HIT_A_H
#define WIP_A_HIT_A_H

#include "engine/functions.h"

// Original names with signature (C++ linkage)
BOOL hit_rupeelike(Entity *e, Entity *t, u8 mode);
BOOL hit_icerobe(Entity *e, Entity *t, u8 mode);

// Hit handlers without an original name (plain names, C linkage)
extern "C" {
BOOL hit_none(Entity *e, Entity *t, u8 mode);   // was hit_none
BOOL hit_shield(Entity *e, Entity *t, u8 mode); // was FS_UnloadOverlayImage (misnamed), 0x02024b28
}

#endif
