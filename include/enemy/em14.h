#ifndef WIP_A_EM14_H
#define WIP_A_EM14_H

#include "enemy/em13.h"

extern const EntityFunc em14_stateTable[];
extern const EntityFunc em14_actionTable[];
extern const u8 em14_hitbox[];

void WizGetTarget(Entity *e);
BOOL em14_getpos_03cbe4(Entity *e);

#endif
