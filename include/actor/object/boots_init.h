#ifndef ACTOR_OBJECT_BOOTS_INIT_H
#define ACTOR_OBJECT_BOOTS_INIT_H

#include "engine/entity.h"

// boots_init and boots_move keep their original C++ names
void boots_init(Entity *e);  // original boots_init(OBJ_WORK_*)
extern "C" {
void *zMalloc(u16 size); // plain symbol (hitdecls.h declares it with C++ linkage)
}
void boots_move(Entity *e);

#endif
