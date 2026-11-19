#ifndef ACTOR_ENEMY_EM28_DIR_H
#define ACTOR_ENEMY_EM28_DIR_H

#include "engine/functions.h"
#include "actor/enemy/em28.h"

int bgcheck(Entity *e, u8 direction);  // original bgcheck(OBJ_WORK_*, unsigned char), 0x02041498
int getDushDir(Entity *e);             // original getDushDir(OBJ_WORK_*), 0x020415f4

#endif
