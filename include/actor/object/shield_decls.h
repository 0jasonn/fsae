#ifndef WIP_SHIELD_DECLS_H
#define WIP_SHIELD_DECLS_H

#include "engine/entity.h"

extern u8 localPlayerIndex;     // 0x0212c504, index of the local player
void shieldMove(Entity *e);     // original shieldMove(OBJ_WORK_*), defined in actor/object/shield.cpp

#endif
