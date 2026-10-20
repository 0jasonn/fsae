#ifndef WIP_A_SET41_H
#define WIP_A_SET41_H

#include "engine/functions.h"

// Actor fields of the Set41 family (file-local overlay).
typedef struct Vars_Set41 {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits;  // ParseTypeBits(type2)
    /* 64 */ u16 counter;   // starts at the timer, +0x1f4 when the timer is in the list below
} Vars_Set41;

// 12 timer values that give the counter its bonus (set41Timers, copied into a local array in set41_init).
typedef struct Set41TimerList {
    u8 values[12];
} Set41TimerList;

extern const EntityFunc set41Table[];       // set41Table, indexed by action
extern "C" void func_02085fac(Entity *e);
extern const u8 set41Hitbox[];              // set41Hitbox
extern u32 em12_typeMasks[];
extern u8 data_0212c7c8[];                  // flag bytes at 0x5c, read by set41_wait
extern const Set41TimerList set41Timers; // set41Timers

#endif
