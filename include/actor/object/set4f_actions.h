#ifndef ACTOR_OBJECT_SET4F_ACTIONS_H
#define ACTOR_OBJECT_SET4F_ACTIONS_H

#include "engine/entity.h"

// RewCell id per actor type
extern const u16 set4f_rewriteIds[];

extern "C" {
void set4f_move(Entity *e);
}

#endif
