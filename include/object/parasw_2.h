#ifndef UNKNOWN_WIP_F_PARASW_2_H
#define UNKNOWN_WIP_F_PARASW_2_H

#include "object/setcommon.h"

// Helpers defined in src/object/set1a.cpp (original names check_flag / check_next).
int check_flag(unsigned long mask, unsigned char start, unsigned char count);
int check_next(unsigned long mask, unsigned char start, unsigned char count);

// Action dispatch tables of the parasw actors (parasw01_actions / parasw02_actions, renamed in scratch/agentF/renames.txt).
extern const EntityFunc parasw01_actions[];
extern const EntityFunc parasw02_actions[];
extern const EntityFunc parasw_typeActions[]; // indexed by e->type (parasw_typeActions, renamed in scratch/agentF/renames.txt)

#endif
