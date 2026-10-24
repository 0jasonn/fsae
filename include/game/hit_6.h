#ifndef WIP_A_HIT_6_H
#define WIP_A_HIT_6_H

// Callees and data of the hit units (sixth unit) that functions.h and game/hitdecls.h do not declare yet.
#include "engine/functions.h"
#include "game/hitdecls.h"

extern "C" void func_0208ab50(Entity *e); // thumb label, no original name
extern u8 data_0212cebc[];                 // per-type flags of the fire and ice hits (stride 0x94)
extern u8 data_0212ced8[];                 // PlayerData.entity pointers (stride 0x94), the damage object of a type
extern u8 data_020ce53c[];                 // table indexed by the animation state of the target

#endif
