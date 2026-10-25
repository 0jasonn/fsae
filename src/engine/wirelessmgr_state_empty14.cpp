#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wirelessmgr_d.h"

// Empty update states 14 and 15 (0x020932f4, 0x020932f8).
extern "C" void Knife_Comm_WirelessManager_update_empty14(void *self);
extern "C" void Knife_Comm_WirelessManager_update_empty15(void *self);
ARM void Knife_Comm_WirelessManager_update_empty14(void *self) {
}

ARM void Knife_Comm_WirelessManager_update_empty15(void *self) {
}
