#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/comm.h"

// Functions in this file (module com, original names from the debug build): CommInfoTask (CommInfoTask())

extern u8 data_0212c500;
extern void (*const data_020f25a8[])(void); // info task table, indexed by data_0212c500

// CommInfoTask (0x02028b34): calls the info task for data_0212c500.
ARM void CommInfoTask(void) {
    data_020f25a8[data_0212c500]();
}
