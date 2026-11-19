#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/comm/comm.h"

#include "engine/com_work.h"

// com_waitsync (0x02028a64): state 0 moves on with the counter cleared. State 1 sends status 0x60; after 0x1e frames
// it moves on and sets +8 to 4. Other states send 0x60 too and, after 0xb4 frames, run func_0202809c and Task_Chain(8).
void com_waitsync(void) {
    u8 state;
    u8 count;

    state = comWork.phase;
    switch (state) {
    case 0:
        comWork.counter = 0;
        comWork.phase = comWork.phase + 1;
        return;
    case 1:
        comWork.send.tag = 0x60;
        if (CommStatusSync(0x60) != 0) {
            ComFinish(1);
            return;
        }
        count = comWork.counter = comWork.counter + 1;
        if (count < 0x1e) {
            return;
        }
        comWork.phase += 1;
        comWork.result = 4;
        return;
    default:
        comWork.send.tag = 0x60;
        if (CommStatusSync(0x60) != 0) {
            ComFinish(1);
            return;
        }
        count = comWork.counter = comWork.counter + 1;
        if (count < 0xb4) {
            return;
        }
        func_0202809c();
        Task_Chain(8);
        return;
    }
}
