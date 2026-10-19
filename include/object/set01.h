#ifndef UNKNOWN_WIP_F_SET01_H
#define UNKNOWN_WIP_F_SET01_H

#include "object/setcommon.h"

// Set01 actor fields (file-local overlay for src/object/set01.cpp, not shared).
typedef struct Vars_Set01 {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u8 stageLevel; // 1..3, picked from the elapsed time in set01_init (data_0212c7c8 + 0x1c)
} Vars_Set01;
#define VSET01(e) VARS(Vars_Set01, e)

extern const EntityFunc set01_actions[]; // set01_actions, indexed by e->action
extern const u8 data_020d410c[];          // indexed by e->type
extern const u8 data_0212c81c[];          // indexed by e->timer
extern const u8 *const *const data_020f26dc[]; // indexed by data_020d410c[type], then data_0212c81c[timer], then random

#endif
