#ifndef ENGINE_COMM_DTORS_API_H
#define ENGINE_COMM_DTORS_API_H

// Functions defined in src/engine/comm_dtors*.cpp.

#include "engine/entity.h"

extern "C" {
void *Knife_Comm_ChildInfo_dtor_ChildInfo(void *self);
void *Knife_Comm_ParentInfo_dtor_ParentInfo(void *self);
}

#endif
