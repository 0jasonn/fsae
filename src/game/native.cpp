#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   nativeInitialize

// Calls the init routine stored for the area (kind 7), if there is one
ARM void nativeInitialize(u8 area) {
    void (*init)(u8);

    init = (void (*)(u8))GetInfoAdrs(area, 7);
    if (init != 0) {
        init(area);
    }
}
