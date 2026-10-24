#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Stores the value through the pointer when it is set and reports 1; reports 0 for a null pointer (dsd name StoreByteIfNonNull_02005c90).
ARM int StoreByteIfNonNull_02005c90(u8 *target, u8 value) {
    if (target == NULL) {
        return 0;
    }
    *target = value;
    return 1;
}
