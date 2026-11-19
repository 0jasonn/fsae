#ifndef ACTOR_OBJECT_SET54_ACTIONS_H
#define ACTOR_OBJECT_SET54_ACTIONS_H

#include "engine/entity.h"

// Door tile tables (6 cells per door type), selected by gameState.unk_01 and the type bit 2
extern const u16 set54_moveTableG1A[];
extern const u16 set54_moveTableG0B[];
extern const u16 set54_openTableG0[];
extern const u16 set54_moveTableG0A[];
extern const u16 set54_openTableG1[];
extern const u16 set54_moveTableG1B[];

extern "C" {
void set54_open(Entity *e);
void set54_move(Entity *e);
}

#endif
