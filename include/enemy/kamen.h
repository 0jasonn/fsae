#ifndef WIP_B_KAMEN_H
#define WIP_B_KAMEN_H

#include "engine/functions.h"

// Kemuri (smoke) puff step of kamen: spawns a puff effect every 8 frames while the u8 at 0x70 counts down.
void kamen_kemuriSet(Entity *e);

// Fields of kamen that the kemuri and init code use.
typedef struct Vars_kamen {
    u8 unk_00[0x70];
    u8 kemuriTimer; // 0x70, counts down to the next puff
} Vars_kamen;

#define V_KAMEN(e) VARS(Vars_kamen, e)

#endif
