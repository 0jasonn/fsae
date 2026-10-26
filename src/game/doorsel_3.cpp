#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "enemy/decls_b2.h"

// Functions in this file (module doorsel, third unit; doorsel.cpp and doorsel_2.cpp hold the others):
//   doorsel_shutter (doorsel_shutter())

// The shutter steps are kept in data_0212c4dc: 0 starts the shutter with a 30 frame timer, 1 counts it down and
// closes, 2 runs the shutter frames until the display shadow reaches 0x60, then advances data_0212c500.
// Timer: u16 at 4 of data_021349c0 (ResultState). Shadow: u16 at 0x18 of data_0212c75c (DisplayShadow).

// doorsel_shutter (0x0202adc8)
ARM void doorsel_shutter(void) {
    u8 step = data_0212c4dc;

    switch (step) {
    case 0:
        *(u16 *)(data_021349c0 + 4) = 0x1e;
        data_0212c4dc = step + 1;
        break;
    case 1:
        *(u16 *)(data_021349c0 + 4) = *(u16 *)(data_021349c0 + 4) - 1;
        if (*(u16 *)(data_021349c0 + 4) != 0) {
            return;
        }
        data_0212c4dc = step + 1;
        keyClear();
        *(u16 *)(data_021349c0 + 4) = 0;
        SoundReq(0x7c);
        break;
    case 2:
        if (CommFrameSync() == 0) {
            return;
        }
        CommUpdateJoy();
        *(u16 *)(data_021349c0 + 4) = *(u16 *)(data_021349c0 + 4) + 1;
        if (*(u16 *)(data_021349c0 + 4) & 1) {
            *(u16 *)(data_0212c75c + 0x18) = *(u16 *)(data_0212c75c + 0x18) + 1;
        }
        if (data_0212c58c[0] & 1) {
            *(u16 *)(data_0212c75c + 0x18) = 0x60;
        }
        if (*(u16 *)(data_0212c75c + 0x18) > 0x60) {
            data_0212c500 = data_0212c500 + 1;
            data_0212c4dc = 0;
            SoundReq(0x7d);
        }
        CommFrameUpdate();
        break;
    }
}
