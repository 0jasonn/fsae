#ifndef GAME_COCKPIT_MOVE_H
#define GAME_COCKPIT_MOVE_H

#include "engine/entity.h"
#include "game/cockpit.h"   // cockpit_move and its callees

extern "C" {
void EffectSet(Entity *e, int kind, int arg);
}

#endif
