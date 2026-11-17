#ifndef ACTOR_ENEMY_EM21_BUTTOBI_H
#define ACTOR_ENEMY_EM21_BUTTOBI_H

#include "engine/functions.h"

extern "C" {
void func_02084828(Entity *e); // thumb helper, no original name yet (moves the entity with its direction and speed)
}

// Knock-back step of em21 (original em21_buttobi(OBJ_WORK_*)), 0x0203f228.
void em21_buttobi(Entity *e);

#endif
