#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/fs/fs_api.h"

void FS_InitFatDriver(void) {
    if (data_0212981c.fatInitialised != 0) {
        return;
    }
    data_0212981c.fatInitialised = 1;
    func_02188f10();
}
