#ifndef ACTOR_OBJECT_SET6B_REWDOOR_H
#define ACTOR_OBJECT_SET6B_REWDOOR_H

#include "engine/functions.h"
#include "engine/player.h"
#include "actor/object/rewhalf.h"

extern const u16 *const rewDoorListsBgmA[];   // 0x020d9380, indexed by a bgm row byte (type bit 2 clear)
extern const u16 *const rewDoorListsBgmB[];   // 0x020d93bc, indexed by a bgm row byte (type bit 2 set)
extern const u16 *const rewDoorListsPickA[];  // 0x020d9308, indexed by the pick index (type bit 2 clear)
extern const u16 *const rewDoorListsPickB[];  // 0x020d92d0, indexed by the pick index (type bit 2 set)

// C++ linkage (original rewDoor(OBJ_WORK_*), symbols.txt set6b_rewDoor)
void set6b_rewDoor(Entity *e);

#endif
