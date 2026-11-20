#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "engine/entity.h"

void PlWeaponFireCheck(Entity *e); // original PlWeaponFireCheck(OBJ_WORK_*)
void PlWorkReset(void);
void PlayerTrans(void);             // 0x02054d30

#endif
