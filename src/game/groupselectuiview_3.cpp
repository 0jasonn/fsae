#include "engine/functions.h"
#include "global.h"
#include "game/uiobject.h"
#include "game/groupselectuiview.h"

// Functions in this file (original names from the debug build):
//   groupSelectUIView::clearRoom (0x020b0d58)

// groupSelectUIView::clearRoom (0x020b0d58): forgets all rooms
ARM void groupSelectUIView::clearRoom(void) {
    u32 i;

    roomCount = 0;
    for (i = 0; i < 4; i++) {
        slots[i].active = 0;
    }
}
