#include "engine/functions.h"
// Implementer B, round 4: nextset (0x02044324), EndingFinish -> EndingFinish (guessed name), EndingTask (0x0204437c).

#include "enemy/encnt.h"
#include "global.h"

ARM void nextset(void) {
    u8 range = encntState.timerRange;
    encntState.count = 0;
    encntState.timer = encntState.timerBase + (Random() & (range - 1)) - ((u32)range >> 1);
}

// Starts the task chain at 9 and moves the ending phase on to 2.
ARM void EndingFinish(void) {
    Task_Chain(9);
    data_0212c500 = 2;
}

ARM void EndingTask(void) {
    endingTasks[data_0212c500]();
}
