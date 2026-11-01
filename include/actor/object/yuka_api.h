#ifndef ACTOR_OBJECT_YUKA_API_H
#define ACTOR_OBJECT_YUKA_API_H

#include "engine/entity.h"

extern "C" {
int rc_yukaPlMoveCheck(PlayerData *player); // original yukaPlMoveCheck(PL_WORK_*)
void ue_bgcheck(Entity *e);
void shita_bgcheck(Entity *e);
void migi_bgcheck(Entity *e);
void hidari_bgcheck(Entity *e);
}

#endif
