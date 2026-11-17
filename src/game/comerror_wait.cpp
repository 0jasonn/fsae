#include "engine/functions.h"
#include "game/comerror_wait.h"

// comerror_wait (0x02028b58): phase 0 resets the screen and the object work and starts a 0x3c frame wait (the timer
// of the result block effectState); phase 1 counts the wait down and when it runs out starts over and advances
// data_0212c500.
void comerror_wait(void) {
    void *knife;
    u8 state;
    u8 next;

    knife = KnifeApp_getInstance();
    CgLoad(2);
    CgLoad(0x15);
    *(u16 *)0x05000000 = 0;
    data_021355a0 = 0;
    state = data_0212c4dc;
    switch (state) {
    case 0:
        DispReset();
        *(u16 *)0x05000000 = 0;
        data_021355a0 = 0;
        ZeldaFadeFinish();
        subtask_dispReset(1);
        ((u8 *)knife)[0x18] = 0;
        ObjWorkPoolClear();
        ObjMoveInit();
        ComInitState();
        data_0212c4f8 = 0;
        SoundInit();
        SoundReq(0x80010000);
        next = data_0212c4dc + 1;
        effectState.timer = 0x3c;
        data_0212c4dc = next;
        break;
    case 1:
        effectState.timer -= 1;
        if (effectState.timer == 0) {
            data_0212c4dc = 0;
            data_0212c500 += 1;
        }
        break;
    default:
        break;
    }
}
