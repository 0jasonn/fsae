#ifndef ACTOR_OBJECT_EM2A_CORE_H
#define ACTOR_OBJECT_EM2A_CORE_H

#include "engine/functions.h"
#include "engine/player.h"

// Overlay of the boss core part (em2a_core)
typedef struct Vars_Em2aCorePart {
    /* 00 */ u8 unk_00[0x73];
    /* 73 */ u8 ownerIndex;   // player that owns this part
    /* 74 */ u8 subtimerStart;
} Vars_Em2aCorePart;
#define VCP(e) VARS(Vars_Em2aCorePart, e)

extern const void *const em2a_corePartHitboxes[]; // em2a_corePartHitboxes, indexed by the part number in timer
extern u8 data_0212cee8[]; // playerWork[0].stateTimer, stride 0x94 (base of the stride access)

extern "C" void func_0208ab50(Entity *e); // thumb, makes the hit player flash
extern u8 data_0212cebc[];  // playerWork[0].state, stride 0x94

#endif
