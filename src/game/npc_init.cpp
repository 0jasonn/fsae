#include "engine/functions.h"
#include "engine/misc_d.h"
#include "global.h"
#include "types.h"

// Functions in this file (address -> name, pending reviewer apply to symbols.txt):
//   func_0204f978 keeps its name (declared in engine/functions.h)

// Clears the 0xa0 bytes of the scene slot table (data_02134d30)
ARM void func_0204f978(void) {
    MIi_CpuClear16(0, &data_02134d30, 0xa0);
}
