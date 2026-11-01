#ifndef OBJECT_OBJDISPATCH_API_H
#define OBJECT_OBJDISPATCH_API_H

// Functions defined in src/object/objdispatch*.cpp.

#include "engine/entity.h"

extern "C" {
void objDispatchAction(Entity *e);
void objDispatchPutWork(Entity *e);
}

#endif
