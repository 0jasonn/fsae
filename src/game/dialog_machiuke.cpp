#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/lobby.h"

// Functions in this file (original names from the debug build):
//   dialog_machiuke_joy (0x020b2898)

// dialog_machiuke_joy() (0x020b2898): edge detection of the keys of the four players. The keys that were pressed in
// this frame (new bits) go to data_0212c58c, the current keys become the previous ones, and the key state of the
// machine is copied when the device is not in wireless mode
extern "C" void dialog_machiuke_joy(void);
ARM void dialog_machiuke_joy(void) {
    void *app;
    u32 i;
    u16 keys;
    u16 prev;

    func_020909c8();
    app = KnifeApp_getInstance();
    for (i = 0; i < 4; i++) {
        keys = *(u16 *)(data_0212c9a8 + i * 0x34 + 0x7a);
        prev = ((u16 *)data_0212c584)[i];
        ((u16 *)data_0212c58c)[i] = keys & (keys ^ prev);
        ((u16 *)data_0212c584)[i] = keys;
    }
    if (KnifeApp_isWirelessMode(app) == 0) {
        *(u16 *)data_0212c58c = *(u16 *)data_0212c514;
        *(u16 *)(data_0212c9a8 + 0x7a) = *(u16 *)data_0212c514;
    }
    *(u16 *)(data_0212c9a8 + 0x12) = *(u16 *)data_0212c514;
}
