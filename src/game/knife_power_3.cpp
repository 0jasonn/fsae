#include "engine/functions.h"
#include "global.h"
#include "game/decls_g.h"

// Functions in this file (original names from the debug build):
//   Knife_GetPowerManager (provisional name Knife_GetPowerManager, the accessor of the PowerManager object)

// Knife_GetPowerManager() (0x020c8104): constructs the PowerManager object at data_0218709c on the first call
// (bit 0 of data_0218708c marks it as built), registers its destructor and returns the object
extern "C" void *Knife_GetPowerManager(void);
ARM void *Knife_GetPowerManager(void) {
    if ((data_0218708c & 1) == 0) {
        Knife_PowerManager_PowerManager(data_0218709c);
        Chain_Push(data_0218709c, Knife_PowerManager_dtorComplete_PowerManager, data_02187090);
        data_0218708c |= 1;
    }
    return data_0218709c;
}
