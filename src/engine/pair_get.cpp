#include "engine/functions.h"
#include "engine/pair_block.h"
#include "global.h"
#include "types.h"

extern "C" u64 Pair_GetIfEnabled(void);

// Pair_GetIfEnabled() (0x02019ccc): returns the 64-bit pair at the pointer in the block when bit 0 of its flags is set,
// otherwise 0.
ARM u64 Pair_GetIfEnabled(void) {
    if (data_02129cac.flags & 1) {
        return *(u64 *)data_02129cac.pair;
    }
    return 0;
}
