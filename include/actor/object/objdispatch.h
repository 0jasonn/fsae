#ifndef ACTOR_OBJECT_OBJDISPATCH_H
#define ACTOR_OBJECT_OBJDISPATCH_H

#include "engine/functions.h"

// State table indexed by e->objId (data_02116588), used by objDispatchClearContact
extern const EntityFunc data_02116588[];
extern "C" {
void objDispatchAction(Entity *e);
void objDispatchPutWork(Entity *e);
}

#endif
