#ifndef WIP_B_DECLS_B_H
#define WIP_B_DECLS_B_H

// Functions used by the implementer B files that are not in engine/functions.h yet.
#include "engine/functions.h"

void shadowSet(Entity *e);              // original shadowSet(OBJ_WORK_*)
void func_02084a20(Entity *e);          // thumb helper, dsd name
extern "C" void AddHeart(Entity *e, s32 amount); // original AddHeart (unmangled)

void ComFinish(u32 a);                    // original ComFinish(unsigned long)
void MultiSioInit(void);                 // original MultiSioInit()

extern "C" void Knife_Single_SinglePlay_SetContNo(void *self, u8 no); // original Knife::Single::SinglePlay::SetContNo(unsigned char), flat name

#endif
