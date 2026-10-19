#include "engine/functions.h"
#include "global.h"
#include "game/shikake.h"

// Switch-block module, third unit. Original names from the debug build.
//   ShikakeInit

// Clears both record counts.
ARM void ShikakeInit(void) {
    data_021348e4 = 0;
    data_021348f0 = 0;
}
