#ifndef WIP_D_DECLS_H
#define WIP_D_DECLS_H

// Declarations used by the D units that are not in engine/functions.h yet. The signatures come from the callers
// (see the report): func_02083d18 has its (Entity *, int, int) signature from the debug build symbol.

#include "engine/entity.h"

BOOL DoorTypeCheck(Entity *e);
int func_02083d18(Entity *e, int dx, int dy);
void func_0208366c(s32 layer, u16 index, u16 size);
void knife_rewDoor(Entity *e, const u16 *table);
void func_020859a0(Entity *e, u8 a, u8 b);
void func_02085934(Entity *e, u8 mode);

#endif
