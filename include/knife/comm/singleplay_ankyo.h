#ifndef KNIFE_COMM_SINGLEPLAY_ANKYO_H
#define KNIFE_COMM_SINGLEPLAY_ANKYO_H

#include "engine/functions.h"
#include "engine/player.h"
#include "knife/comm/singleplay_2.h"

// SinglePlay functions (plain names, `this` as void *).
extern "C" {
BOOL Knife_Single_SinglePlay_CheckAnkyo_094a88(void *self, u8 kind, Entity *e, s16 x, s16 y);
BOOL Knife_Single_SinglePlay_CheckAnkyo_094b08(void *self, PlayerData *player);
}

#endif
