#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (provisional name for a func_ address):
//   nameEntryUIView_clampGroup nameEntryUIView_clampGroup (0x020af380)

// nameEntryUIView_clampGroup (0x020af380): when the mode at offset 0x46 is 1 to 4, moves the value at *group into the
// range of that mode (0 to 2, 3 to 6, 7 to 9, 10 to 12) by setting it to the first value of the range if it is outside
ARM void nameEntryUIView_clampGroup(void *self, s8 *group) {
    switch ((s8)((u8 *)self)[0x46]) {
    case 1:
        if (*group < 0 || *group > 2) {
            *group = 0;
        }
        break;
    case 2:
        if (*group < 3 || *group > 6) {
            *group = 3;
        }
        break;
    case 3:
        if (*group < 7 || *group > 9) {
            *group = 7;
        }
        break;
    case 4:
        if (*group < 10 || *group > 12) {
            *group = 10;
        }
        break;
    }
}
