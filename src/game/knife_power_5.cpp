#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/knife_power_5_api.h"

// Knife::PowerManager destructors. The complete destructor (0x020c83a0) has an empty body. The deleting destructor
// (0x020c83a4) frees the block through operator delete and returns it.

void Knife_PowerManager_dtorComplete_PowerManager(void *self) {
}

void *Knife_PowerManager_dtor_PowerManager(void *self) {
    operator delete(self);
    return self;
}
