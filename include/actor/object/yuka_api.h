#ifndef ACTOR_OBJECT_YUKA_API_H
#define ACTOR_OBJECT_YUKA_API_H

#include "engine/entity.h"
#include "engine/bg_buff.h"

extern "C" {
int rc_yukaPlMoveCheck(PlayerData *player); // original yukaPlMoveCheck(PL_WORK_*)
void ue_bgcheck(Entity *e, BG_BUFF_ *bgBuffer);     // original ue_bgcheck(OBJ_WORK_*, BG_BUFF_*)
void shita_bgcheck(Entity *e, BG_BUFF_ *bgBuffer);  // original shita_bgcheck(OBJ_WORK_*, BG_BUFF_*)
void migi_bgcheck(Entity *e, BG_BUFF_ *bgBuffer);   // original migi_bgcheck(OBJ_WORK_*, BG_BUFF_*)
void hidari_bgcheck(Entity *e, BG_BUFF_ *bgBuffer); // original hidari_bgcheck(OBJ_WORK_*, BG_BUFF_*)
void yukaCheck(Entity *e);     // original yukaCheck(OBJ_WORK_*)
}

#endif
