#include "engine/functions.h"
#include "global.h"
#include "game/uiobject.h"
#include "game/groupselectuiview.h"

// Functions in this file (original names from the debug build):
//   groupSelectUIView::getNumOfRoom (0x020b07bc)

// groupSelectUIView::getNumOfRoom (0x020b07bc): number of rooms at the start of the list that are still in use
// (state above 8); the count stops at the first room that is not
ARM s32 groupSelectUIView::getNumOfRoom(void) const {
    s32 count;
    u32 i;

    count = 0;
    for (i = 0; i < roomCount; i++) {
        if (rooms[i]->state <= 8) {
            break;
        }
        count++;
    }
    return count;
}
