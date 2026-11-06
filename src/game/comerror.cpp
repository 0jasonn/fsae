#include "engine/functions.h"
#include "engine/misc.h"
#include "knife/app/knife_hud.h"
#include "game/comerror.h"

// Functions in this file (original names from the debug build):
//   comerror_move (0x02028e70)

// comerror_move() (0x02028e70): per-frame update of the communication error screen. State 0 runs the countdown and
// starts the fade-out when the countdown has ended; state 1 resets the display and the object tables and returns to
// the task chain. Every other path (and state 0) ends by calling the function in data_0212c564 and func_020830ec.
void comerror_move(void) {
    u8 *app;

    app = (u8 *)KnifeApp_getInstance();
    CgLoad(2);
    CgLoad(0x15);
    switch (data_0212c4dc) {
    case 0:
        ((Knife::Hud::HudManager *)(app + 0x1f8))->update(data_0212c4c8);
        *(u16 *)0x05000000 = 0;
        data_021355a0 = 0;
        displayState.displayFlags = displayState.displayFlags & 0xfeff;
        if (*(u16 *)(effectState + 4) != 0) {
            *(u16 *)(effectState + 4) = *(u16 *)(effectState + 4) - 1;
            if (*(u16 *)(effectState + 4) == 0) {
                ((Knife::Hud::HudManager *)(app + 0x1f8))->setStateThree();
            }
        }
        if (*(u16 *)(effectState + 4) == 0 && (data_0212c510 & 1)) {
            SoundReq(0x3e);
            FadeSet(3, 8);
            data_0212c4dc = data_0212c4dc + 1;
        }
        break;
    case 1:
        ((Knife::Hud::HudManager *)(app + 0x1f8))->update(data_0212c4c8);
        if (blendRequest.blendEnabled != 0) {
            return;
        }
        DispReset();
        *(u16 *)0x05000000 = 0x6739;
        data_021355a0 = 0x6739;
        ObjMoveInit();
        ObjWorkPoolClear();
        Task_Chain(7);
        func_020827a8(2);
        return;
    default:
        break;
    }
    data_0212c564();
    func_020830ec();
}
