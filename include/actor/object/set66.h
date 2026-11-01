#ifndef WIP_D_SET66_H
#define WIP_D_SET66_H

// Set66 actor family (module set66) and the rr type0/type1 helpers. Shared by set66.cpp and set66_2.cpp.

#include "engine/functions.h"
#include "engine/player.h"

extern const EntityFunc set66_typeActions[];  // set66_typeActions, indexed by e->type
extern const EntityFunc set66_type0Actions[]; // set66_type0Actions, indexed by e->action
extern const EntityFunc set66_type1Actions[]; // set66_type1Actions, indexed by e->action
extern const EntityFunc set67_actions[];     // set67_actions, indexed by e->action
extern const EntityFunc set68_typeActions[]; // set68_typeActions, indexed by e->type
extern const EntityFunc set68_type1Actions[]; // set68_type1Actions, indexed by e->action
extern const EntityFunc set69_typeActions[];  // set69_typeActions, indexed by e->type
extern const EntityFunc set69_type0Actions[]; // set69_type0Actions, indexed by e->action
extern u32 em12_typeMasks[];                 // indexed by e->areaIndex; [0] is the game flag word used by set67/68/69
extern const s16 *const rr_type0_posTable[];  // rr_type0_posTable, indexed by player count - 1, (x, y) pairs
extern u8 data_0212c618;                      // flag byte, bss
extern const u32 flagBits[];                  // indexed by e->type2

int plStCheck(PlayerData *player);            // 0x0207553c, defined in set66_2.cpp
int VGroupLoadWait(Entity *e);                // 0x020811a8, nonzero while the VRAM group load is pending
void rr_poscopy(Entity *e, Entity *target);   // 0x02075528, defined in set66_2.cpp

// File-local overlay. 0x53 selects the VRAM block for the character load, 0x60 is the rupee rush bitmask
// (ParseTypeBits, one bit per spawn slot).
typedef struct Vars_Set66 {
    /* 00 */ u8 unk_00[0x53];
    /* 53 */ u8 vramSlot;
    /* 54 */ u8 unk_54[0x60 - 0x54];
    /* 60 */ u32 typeBits;
    /* 64 */ u8 unk_64[0x7c - 0x64];
    /* 7c */ u16 vanishTimer; // counts down while the rr type1 object shrinks away
} Vars_Set66;

void rr_plset(Entity *e);                     // 0x02076620, defined later in the set69 range
extern u8 data_0212c648[];                    // shared block: Entity * at +0, s16 fields at +0x20 / +0x22

#endif
