#ifndef WIP_A_SET42_H
#define WIP_A_SET42_H

#include "engine/functions.h"
#include "engine/player.h"

extern const EntityFunc set42Table[]; // set42Table, indexed by action
extern s16 scrollArgs[3];             // scrollArgs, scroll arguments for ObjAffineSet2
void func_02085934(Entity *e, u8 a);
void func_020859a0(Entity *e, u8 a, u8 b);

#endif
