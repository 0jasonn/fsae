#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (module coloradjust, original names from the debug build):
//   func_02029a50 (clears dst with MIi_CpuClearFast, declared in functions.h), SetColorAdjust (SetColorAdjust(unsigned long))

extern const u8 data_020cfabc[]; // colour adjust table 0
extern const u8 data_020cfb7c[]; // colour adjust table 2
extern const u8 *data_020f2a18;  // selected colour adjust table, NULL for none

// func_02029a50 (0x02029a50): clears size bytes at dst with the fast clear (value 0).
ARM void func_02029a50(void *dst, u32 size) {
    MIi_CpuClearFast(0, dst, size);
}

// SetColorAdjust (0x02029a68): selects table 0 for mode 0, table 2 for mode 2 and no table otherwise.
ARM void SetColorAdjust(u32 mode) {
    switch (mode) {
    case 0:
        data_020f2a18 = data_020cfabc;
        return;
    case 2:
        data_020f2a18 = data_020cfb7c;
        return;
    default:
        data_020f2a18 = NULL;
        return;
    }
}
