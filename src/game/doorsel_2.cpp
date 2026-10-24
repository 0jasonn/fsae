#include "engine/functions.h"
#include "global.h"

// doorsel_sync (0x0202ab90): advances the door select step data_0212c500 and clears the sub-step data_0212c4dc.
//   doorsel_sync (0x0202ab90)

extern "C" void doorsel_sync(void);

extern u8 data_0212c4dc;
extern u8 data_0212c500;

ARM void doorsel_sync(void) {
    data_0212c500 = data_0212c500 + 1;
    data_0212c4dc = 0;
}
