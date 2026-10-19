#include "engine/functions.h"
// Functions in this file:
//   isBossFloor -> isBossFloor
//   shuffleStage -> shuffleStage
#include "game/gamestateview_c.h"
#include "global.h"

ARM BOOL isBossFloor(void) {
    data_0212c7c8.periodicFlag = (data_0212c7c8.phaseTimer % 3 == 2) ? 0x81 : 0;
    return data_0212c7c8.periodicFlag != 0;
}

ARM void shuffleStage(void) {
    u8 oldIndex = data_0212c7c8.pickIndex;
    u8 newIndex;
    do {
        newIndex = Random() & 3;
        data_0212c7c8.pickIndex = newIndex;
    } while (newIndex == oldIndex);
}
