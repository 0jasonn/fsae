#include "engine/functions.h"
#include "global.h"

// yousei demo, from 0x02082598: goto_nextdemo sets the demo step to 3 and clears data_0212c4dc.

extern u8 data_0212c500;
extern u8 data_0212c4dc;

// goto_nextdemo (0x02082598)
ARM void goto_nextdemo(void) {
    data_0212c500 = 3;
    data_0212c4dc = 0;
}
