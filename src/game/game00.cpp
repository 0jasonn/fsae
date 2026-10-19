#include "engine/functions.h"
#include "game/multiplay.h"
#include "global.h"

// game00_select (0x02047454): runs the task for the current phase byte.
ARM void game00_select(void) {
    game00TaskTable[data_0212c500]();
}
