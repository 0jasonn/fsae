#ifndef UNKNOWN_WIP_F_SET02_H
#define UNKNOWN_WIP_F_SET02_H

#include "engine/functions.h"
#include "object/setcommon.h"

// Set02 actor tables (renamed in scratch/agentF/renames.txt).
extern const EntityFunc set02_actions[];     // set02_actions, indexed by e->action (types below 0x17)
extern const EntityFunc set02_typeActions[]; // set02_typeActions, indexed by e->type - 0x17

// 8-byte setup entry per type: s16 x, s16 y, s16 speed, u8 spriteSettings bits 14..15, u8 bits 30..31.
typedef struct Set02Setup {
    s16 x;
    s16 y;
    s16 speed;
    u8 bitsA;
    u8 bitsB;
} Set02Setup;
extern const Set02Setup set02_setupTable[]; // data_0211566c


#endif
