#include "engine/functions.h"
#include "engine/misc.h"

extern "C" void func_0208ae14(void);

// bg2StSet, 0x02057494. In the modes that use the second background (0, 1, 2 and 6) it takes the scroll value from
// the background table, sets the map mode byte to 0xc and turns display bit 0x800 on.
void bg2StSet(void) {
    switch (gameState.unk_01) {
    case 0:
    case 1:
    case 2:
    case 6:
        mapState.unk_0[8] = 0xc;
        displayState.unk_2c = *(const u16 *)(data_020ce4d0 + 0x26);
        displayState.displayFlags |= 0x800;
        func_0208ae14();
        break;
    }
}
