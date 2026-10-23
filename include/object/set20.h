#ifndef WIP_G_SET20_H
#define WIP_G_SET20_H

#include "engine/functions.h"

// Actor fields of the Set20 family (file-local overlay, offsets from the original code).
typedef struct Vars_Set20 {
    /* 00 */ u8 unk_00[0x60];
} Vars_Set20;

extern const EntityFunc set20_stateTable[]; // indexed by e->action, was set20_stateTable
extern const void *set20_hitboxTable[];     // hitbox per frame (frames 0 to 4), was set20_hitboxTable
extern "C" void func_020841b0(Entity *e);  // thumb label, no original name

#endif
