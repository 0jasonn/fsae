#ifndef ACTOR_ENEMY_COMMERROR_H
#define ACTOR_ENEMY_COMMERROR_H

// Declarations for the commerror unit (src/wip/B/commerror.cpp). Not in engine/functions.h yet.
// CommErrorCheck returns 1 when the check passes; game/comm.h declares it void, which the reviewer should fix.
#include "engine/functions.h"
#include "knife/comm/comm.h"

int CommStatusSync(u8 status);        // original CommStatusSync(unsigned char), mangled _Z14CommStatusSynch
extern "C" int comerror_error_check(u8 value); // original error_check(unsigned char), plain name

#endif
