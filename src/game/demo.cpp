#include "engine/functions.h"
#include "knife/comm/com_sio.h"
#include "global.h"
#include "engine/blend_request.h"
#include "game/demo_api.h"
#include "engine/display_state.h"

// Demo module (demo): DemoTask runs the demo phase machine (phase byte data_0212c4dc), demoWaitCk counts down the
// phase timer, DemoBgBuffClear clears the two neighbour grids.
//   DemoTask (0x0202a78c), demoWaitCk (0x0202a8bc), DemoBgBuffClear (0x0202a92c)


extern u8 data_0212c4dc;                // demo phase, 0..4
extern u16 data_0212c510;               // nonzero ends the phase wait early
#include "engine/effect_state.h"
extern u16 data_021355a0;

// DemoTask (0x0202a78c): phase 0 loads the demo graphics and palette, starts the display and waits;
// 1 starts the link and waits for the timer, then fades; 2 leaves phase 3 when the blend is done;
// 3 waits and fades; 4 hands over to task 7 when the blend is done.
void DemoTask(void) {
    u32 *dispCnt;

    switch (data_0212c4dc) {
    case 0:
        displayState.displayFlags = 0x100;
        displayState.bg[0].cnt = 8;
        DataLoad(4);
        CgLoad(3);
        MemClearFast(&effectState, 0x28);
        effectState.timer = 0xf0;
        *(u16 *)0x05000000 = 0;
        data_021355a0 = 0;
        FadeSet(0, 8);
        GX_DispOn();
        dispCnt = (u32 *)0x04001000;
        *dispCnt |= 0x10000;
        data_0212c4dc++;
        break;
    case 1:
        MultiSioInit();
        if (demoWaitCk()) {
            FadeSet(3, 8);
        }
        break;
    case 2:
        if (blendRequest.blendEnabled == 0) {
            data_0212c4dc = 4;
        }
        break;
    case 3:
        if (demoWaitCk()) {
            FadeSet(3, 8);
        }
        break;
    case 4:
        if (blendRequest.blendEnabled == 0) {
            Task_Chain(7);
        }
        break;
    }
}

// demoWaitCk (0x0202a8bc): does nothing while the blend runs. Otherwise counts the timer down and moves to the next
// phase (returns 1) once the timer is 0 or data_0212c510 is set; returns 0 while waiting.
int demoWaitCk(void) {
    if (blendRequest.blendEnabled != 0) {
        return 0;
    }
    effectState.timer = effectState.timer - 1;
    if (data_0212c510 != 0 || effectState.timer == 0) {
        data_0212c4dc++;
        return 1;
    }
    return 0;
}

// DemoBgBuffClear (0x0202a92c): clears the two neighbour grids (0xb004 bytes each).
void DemoBgBuffClear(void) {
    extern u8 data_02158fa0[];
    extern u8 data_02163fa4[];

    OSi_CpuClear32(0, data_02158fa0, 0xb004);
    OSi_CpuClear32(0, data_02163fa4, 0xb004);
}
