#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/fatfs/fatfs_wrap_api.h"

// Tail call to FATFSi_SendToPXI.
u32 Fatfs_SendToPxi(u32 a, u32 b, u32 c, u32 d) {
    return FATFSi_SendToPXI(a, b, c, d);
}
