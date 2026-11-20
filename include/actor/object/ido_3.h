#ifndef WIP_C_IDO_3_H
#define WIP_C_IDO_3_H

#include "engine/functions.h"

// Callees of the ido wait state that engine/functions.h does not declare yet.
extern "C" int ido_yukaPlMoveCheck(PlayerData *player); // original yukaPlMoveCheck(PL_WORK_*), src/object/ido_2.cpp

#endif
