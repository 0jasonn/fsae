#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/m4a.h"
#include "engine/knife_tokenizer.h"

// KnifeApp::getZelmapResource (0x0208de38) and KnifeApp::isWirelessMode (0x0208de54).
extern u8 *data_02171e14;
extern u8 data_0212c4fc[];

// KnifeApp::getZelmapResource (0x0208de38): an entry of the map table. Even ids are offsets from the table base, odd ids
// are the raw entry.
extern "C" u32 KnifeApp_getZelmapResource(void *app, u32 id);
ARM u32 KnifeApp_getZelmapResource(void *app, u32 id) {
    u32 *table;
    u32 value;

    table = (u32 *)data_02171e14;
    value = table[id];
    if ((id & 1) == 0) {
        return (u32)table + value;
    }
    return value;
}

// KnifeApp::isWirelessMode (0x0208de54): true when the wireless mode flag is set, or when the wireless manager has a
// state other than zero
extern "C" int KnifeApp_isWirelessMode(void *a);
ARM int KnifeApp_isWirelessMode(void *a) {
    u8 *manager;

    manager = (u8 *)func_020909c8();
    if (data_0212c4fc[0] != 0) {
        return 1;
    }
    if (*(u32 *)(manager + 0x1c9c) != 0) {
        return Knife_Comm_WirelessManager_getState(manager) != 0;
    }
    return 0;
}
