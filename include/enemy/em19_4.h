#ifndef WIP_B_EM19_4_H
#define WIP_B_EM19_4_H

#include "engine/functions.h"
#include "enemy/effectset.h"
#include "enemy/waitset.h"

extern const u8 em19_hitbox[];          // em19_hitbox, hitbox of em19
extern const u16 em19_poseTable[];      // em19_poseTable, pose per parent type
extern const EntityFunc em19_stateTable[]; // em19_stateTable, GenericKnockback table of em19

void bgobj_moveset(Entity *e, u8 moveId); // original moveset(OBJ_WORK_*, unsigned char), see enemy/bgobj.h
void setActionAnim3(Entity *e);          // original setActionAnim3(OBJ_WORK_*)

// Actor-specific fields of em19 (Entity offsets 0x70 onwards).
typedef struct Vars_em19 {
    u8 unk_00[0x70];
    u16 waitTimer;   // 0x70: frames to wait before the next check
    u8 lastHealth;   // 0x72: health seen at the last update (a change means a hit)
    u8 moveTimer;    // 0x73: frames until the next hop decision
} Vars_em19;

#endif
