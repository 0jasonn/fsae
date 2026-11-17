#ifndef ACTOR_OBJECT_SET33_ACTIONS_H
#define ACTOR_OBJECT_SET33_ACTIONS_H

#include "engine/entity.h"

extern const u16 set33SpeedTable[]; // initial speed per type
extern const u8 set33Unk2eTable[];  // unk_2e per type

extern "C" {
void set33_lift(Entity *e);
}

#endif
