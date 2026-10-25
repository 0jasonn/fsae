#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wirelessmgr_d.h"

// Empty update state 0 (0x02092940): nothing to do in the off state.
extern "C" void Knife_Comm_WirelessManager_update_empty0(void *self);
ARM void Knife_Comm_WirelessManager_update_empty0(void *self) {
}
