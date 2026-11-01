#ifndef WIP_B_COMMERROR_H
#define WIP_B_COMMERROR_H

// Declarations for the commerror unit (src/wip/B/commerror.cpp). Not in engine/functions.h yet.
// CommErrorCheck returns 1 when the check passes; game/comm.h declares it void, which the reviewer should fix.
#include "engine/functions.h"

int CommStatusSync(u8 status);        // original CommStatusSync(unsigned char), mangled _Z14CommStatusSynch
int CommErrorCheck(u32 a);            // original CommErrorCheck(unsigned long), mangled _Z14CommErrorCheckm
extern "C" int comerror_error_check(u8 value); // original error_check(unsigned char), plain name
void func_0202809c(void);             // dsd name (ComFinish(0)), C++ linkage as in game/comm.h

#endif
