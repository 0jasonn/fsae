#ifndef OBJECT_OBJFIND_API_H
#define OBJECT_OBJFIND_API_H

// Functions defined in src/object/objfind*.cpp.

#include "engine/entity.h"

extern "C" {
Entity *findObj(u8 kind, u8 id);
}

#endif
