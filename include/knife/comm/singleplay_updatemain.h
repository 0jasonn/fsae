#ifndef KNIFE_COMM_SINGLEPLAY_UPDATEMAIN_H
#define KNIFE_COMM_SINGLEPLAY_UPDATEMAIN_H

#include "engine/functions.h"

extern "C" {
void Knife_Single_SinglePlay_Update(void *self, PlayerData *player0, PlayerData *player1, u16 keysDown, u16 keysHeld);
}

#endif
