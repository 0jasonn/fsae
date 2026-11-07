#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/comm/comm.h"

extern u8 comWork[];

// com_waitsync (0x02028a64): state 0 moves on with the counter cleared. State 1 sends status 0x60; after 0x1e frames
// it moves on and sets +8 to 4. Other states send 0x60 too and, after 0xb4 frames, run func_0202809c and Task_Chain(8).
void com_waitsync(void) {
    u8 state;
    u8 count;

    state = comWork[1];
    switch (state) {
    case 0:
        comWork[2] = 0;
        comWork[1] = comWork[1] + 1;
        return;
    case 1:
        comWork[0x10] = 0x60;
        if (CommStatusSync(0x60) != 0) {
            ComFinish(1);
            return;
        }
        count = comWork[2] = comWork[2] + 1;
        if (count < 0x1e) {
            return;
        }
        comWork[1] += 1;
        *(u32 *)(comWork + 8) = 4;
        return;
    default:
        comWork[0x10] = 0x60;
        if (CommStatusSync(0x60) != 0) {
            ComFinish(1);
            return;
        }
        count = comWork[2] = comWork[2] + 1;
        if (count < 0xb4) {
            return;
        }
        func_0202809c();
        Task_Chain(8);
        return;
    }
}
