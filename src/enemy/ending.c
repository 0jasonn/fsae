// Implementer B, round 4: nextset (0x02044324), EndingFinish -> EndingFinish (guessed name), EndingTask (0x0204437c).

#include "enemy/encnt.h"
#include "global.h"

ARM void nextset(void) {
    u8 range = data_02134b48.timerRange;
    data_02134b48.count = 0;
    data_02134b48.timer = data_02134b48.timerBase + (Random() & (range - 1)) - ((u32)range >> 1);
}

// Starts the task chain at 9 and moves the ending phase on to 2.
ARM void EndingFinish(void) {
    Task_Chain(9);
    data_0212c500 = 2;
}

ARM void EndingTask(void) {
    data_020f29fc[data_0212c500]();
}
