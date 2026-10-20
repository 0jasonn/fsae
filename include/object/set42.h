#ifndef WIP_A_SET42_H
#define WIP_A_SET42_H

#include "engine/functions.h"

extern const EntityFunc set42Table[]; // set42Table, indexed by action
extern s16 scrollArgs[3];             // scrollArgs, scroll arguments for ObjAffineSet2
extern u8 data_0212c7c8[];            // shared flag bytes; byte 0x6e is set to 4 by set42_move
void func_02085934(Entity *e, u8 a);
void func_020859a0(Entity *e, u8 a, u8 b);

#endif
