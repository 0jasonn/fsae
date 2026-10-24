#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (provisional name for a func_ address):
//   subTask_staffroll_setFlagOff (0x020ae280): subTask_staffroll_setFlagOff, sets the flag byte to 0xff
// subTask_staffroll_cutout (0x020ae294) is parked in scratch/agentF/nonmatching/subTask_staffroll_cutout.cpp

extern u8 data_02180da8[];

// subTask_staffroll_setFlagOff (0x020ae280): sets the flag byte of the screen state to 0xff
ARM void subTask_staffroll_setFlagOff(void) {
    ((s8 *)data_02180da8)[1] = -1;
}
