#ifndef ENGINE_RET_CONST_API_H
#define ENGINE_RET_CONST_API_H

// Functions defined in src/engine/ret_const*.cpp.

#include "engine/entity.h"

extern "C" {
u32 Obj_CodeForArg(u32 unused, u32 arg);
u32 Stub_ReturnFourA(void);
u32 Stub_ReturnFourB(void);
}

#endif
