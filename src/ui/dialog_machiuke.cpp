#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/lobby.h"
#include "ui/dialog_machiuke_api.h"

// Functions in this file (original names from the debug build):
//   dialog_machiuke_joy (0x020b2898)

// dialog_machiuke_joy() (0x020b2898): edge detection of the keys of the four players. The keys that were pressed in
// this frame (new bits) go to playerKeys, the current keys become the previous ones, and the key state of the
// machine is copied when the device is not in wireless mode
void dialog_machiuke_joy(void) {
    void *app;
    u32 i;
    u16 keys;
    u16 prev;

    func_020909c8();
    app = KnifeApp_getInstance();
    for (i = 0; i < 4; i++) {
        keys = comWork.recv[i].keys;
        prev = ((u16 *)playerKeysPrev)[i];
        ((u16 *)playerKeys)[i] = keys & (keys ^ prev);
        ((u16 *)playerKeysPrev)[i] = keys;
    }
    if (KnifeApp_isWirelessMode(app) == 0) {
        playerKeys[0] = data_0212c514;
        comWork.recv[0].keys = data_0212c514;
    }
    comWork.send.keys = data_0212c514;
}
