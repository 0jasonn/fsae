#include "engine/functions.h"
#include "global.h"
#include "game/yousei.h"

// Yousei demo exit and end, 0x020825bc to 0x020826b0.
//   yousei_exit (0x020825bc): three steps. Waits for the fade (messageRequest low bits == 6), then a message, then
//   sets the demo step to 4 and starts the fades and sounds.
//   yousei_end (0x0208265c): clears the backdrop colour, resets the object and text pools and jumps to task 6.

extern u8 data_0212c4dc;     // demo sub-step
extern u8 data_0212c500;     // demo step
extern u8 messageRequest;
extern u8 data_0212c5ac;     // non-zero while the screen is blanked
extern u16 data_021355a0;

// yousei_exit (0x020825bc)
ARM void yousei_exit(void) {
    switch (data_0212c4dc) {
    case 0:
        if ((messageRequest & 0x7f) == 6) {
            Status_ArmIfEnabled();
            data_0212c4dc = data_0212c4dc + 1;
        }
        break;
    case 1:
        if (yousei_msgFinishWait() == 0) {
            data_0212c500 = 4;
            FadeSet(3, 2);
            SoundReq(2 + 0x210);
            if (func_02081b64() != 0) {
                SoundReq(3 + 0x238);
            }
        }
        break;
    }
}

// yousei_end (0x0208265c)
ARM void yousei_end(void) {
    if (data_0212c5ac != 0) {
        return;
    }
    DispReset();
    *(u16 *)0x5000000 = 0x6739;
    data_021355a0 = 0x6739;
    ObjWorkPoolClear();
    ObjMoveInit();
    MessageInitialize();
    TelopInitialize();
    Task_Chain(6);
}
