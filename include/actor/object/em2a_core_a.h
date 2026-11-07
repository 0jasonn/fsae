#ifndef WIP_A_EM2A_CORE_A_H
#define WIP_A_EM2A_CORE_A_H

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
extern u8 localPlayerIndex;
extern u8 data_0212ced8[]; // playerWork[0].entity, stride 0x94
#define TEMPLATE_ENTITY(i) (*(Entity **)(data_0212ced8 + (i) * 0x94))

// Bit view of PlayerData byte 0x3e / paletteBits: b = bits 2..3
typedef struct PalBits {
    u8 a : 2;
    u8 b : 2;
    u8 c : 3;
    u8 d : 1;
} PalBits;
extern "C" void func_0208ab50(Entity *e); // thumb, makes the hit player flash
extern u8 data_0212cebc[];  // playerWork[0].state, stride 0x94

#endif
