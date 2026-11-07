#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/app/knife_hud.h"
#include "engine/g_calls.h"

// terminateInfo_move() (0x020c8b2c): the per-frame step of the terminate sequence. State 0 waits for the timer
// at effectState + 4, updates the HUD and starts the white-out; state 1 waits for the second timer and starts the
// next subtask. The terminate handler in data_0212c564 and func_020830ec run on every step.
extern u8 data_0212c4dc;   // terminate state
extern u8 blendRequest;   // nonzero while the fade work is busy
extern u8 data_0212c4c8;   // HUD update mode
extern u16 data_0212c510;  // bit 0 requests the white-out
extern u8 effectState[]; // result state block, u16 timer at +4
extern void (*data_0212c564)(void); // terminate handler

void terminateInfo_move(void) {
    u8 *app;
    u8 *block;
    u16 timer;

    app = (u8 *)KnifeApp_getInstance();
    switch (data_0212c4dc) {
    case 0:
        if (blendRequest != 0) {
            return;
        }
        block = effectState;
        timer = *(u16 *)(block + 4);
        if (timer != 0) {
            timer = timer - 1;
            *(u16 *)(block + 4) = timer;
            if (*(u16 *)(block + 4) == 0) {
                ((Knife::Hud::HudManager *)(app + 0x1f8))->setStateThree();
            }
        } else {
            ((Knife::Hud::HudManager *)(app + 0x1f8))->update(data_0212c4c8);
            if ((data_0212c510 & 1) != 0) {
                SoundReq(0x3e);
                FadeSet(3, 8);
                eff_white_out_init(0x888);
                data_0212c4dc++;
                *(u16 *)(block + 4) = 4;
            }
        }
        break;
    case 1:
        if (blendRequest != 0) {
            return;
        }
        timer = *(u16 *)(effectState + 4);
        if (timer != 0) {
            timer = timer - 1;
            *(u16 *)(effectState + 4) = timer;
            if (*(u16 *)(effectState + 4) == 0) {
                Task_Chain(7);
                subTask_game_start_reload();
                func_020827a8(3);
                data_0212c4dc = 1;
            }
        }
        break;
    }
    data_0212c564();
    func_020830ec();
}
