#ifndef UNKNOWN_WIP_F_TAIMATSU_H
#define UNKNOWN_WIP_F_TAIMATSU_H

#include "engine/objwork.h"
#include "object/setcommon.h"

// Taimatsu (torch puzzle) actor tables, renamed in scratch/agentF/renames.txt.
extern const EntityFunc taimatsu00_actions[]; // taimatsu00_actions, indexed by e->action
extern const EntityFunc taimatsu01_actions[]; // taimatsu01_actions, indexed by e->action
extern const u16 taimatsu_pairTable[];        // taimatsu_pairTable, (x, y) u16 pairs
extern u16 data_0213492c[];                   // (x, y) u16 pairs per area (same table as enemy/em12.h)

// Taimatsu actor overlay: u16 words starting at 0x60 hold the packed torch positions.
typedef struct Vars_Taimatsu {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u16 packed[12];
} Vars_Taimatsu;
#define VTP00(e) VARS(Vars_Taimatsu, e)

void taimatsu_clear(Entity *e);
void make_question(Entity *e);
u8 taimatsu_count(Entity *e);

#endif
