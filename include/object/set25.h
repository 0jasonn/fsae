#ifndef WIP_G_SET25_H
#define WIP_G_SET25_H

#include "engine/functions.h"
#include "object/setcommon.h"

// Actor fields of the Set25 family (file-local overlay, offsets from the original code).
typedef struct Vars_Set25 {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u8 timers[4]; // countdown per contacted entity type (0 to 3)
} Vars_Set25;

extern const EntityFunc set25_stateTable[];   // indexed by e->action, was set25_stateTable
extern const u8 *set25_hitboxTable[];         // hitbox per entity type, was set25_hitboxTable
extern "C" void vitaldec(Entity *e, u8 *timer); // original vitaldec(OBJ_WORK_*, unsigned char*)
extern "C" void breakSmokeSet(Entity *e);       // original breakSmokeSet(OBJ_WORK_*)
extern "C" void recell1(Entity *e);             // original recell1(OBJ_WORK_*)

#endif
