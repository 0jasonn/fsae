#ifndef WIP_A_EM15_H
#define WIP_A_EM15_H

#include "enemy/em13.h"

extern const EntityFunc em15_stateTable[];
extern const EntityFunc em15_actionTable[];
extern const u8 em15_hitbox[];
extern const s16 em15_targetOffsets[];

void WizGetTarget(Entity *e);
BOOL em15_getpos_03cf18(Entity *e);

#endif
