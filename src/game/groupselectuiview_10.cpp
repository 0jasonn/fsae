#include "engine/functions.h"
#include "global.h"
#include "game/uiobject.h"
#include "game/groupselectuiview.h"
#include "engine/comm_parentinfo.h"

// Functions in this file (original names from the debug build):
//   groupSelectUIView::updateScan (0x020b0d7c)

// groupSelectUIView::updateScan (0x020b0d7c): marks the rooms, adds every scan result as a room (the players and the
// game info of the scan result give the room its name), then removes the rooms that were not found again
ARM void groupSelectUIView::updateScan(void) {
    void *manager;
    void *scanResult;
    const u16 *info;
    s32 players;
    s32 infoSize;
    s32 scanCount;
    s32 scanIndex;
    u32 i;

    manager = func_020909c8();
    for (i = 0; i < roomCount; i++) {
        rooms[i]->unk_0c = 0;
    }
    scanCount = Knife_Comm_WirelessManager_getMaxParents(manager);
    for (scanIndex = 0; scanIndex < scanCount; scanIndex++) {
        scanResult = Knife_Comm_WirelessManager_getScanResult(manager, scanIndex);
        if (scanResult != NULL) {
            players = ((const Knife::Comm::ParentInfo *)scanResult)->getCurrentPlayers();
            infoSize = ((const Knife::Comm::ParentInfo *)scanResult)->getUserGameInfoSize();
            info = (const u16 *)((const Knife::Comm::ParentInfo *)scanResult)->getUserGameInfo();
            addRoomPane((u8 *)scanResult + 8, info, infoSize, (u8)players, *(u32 *)((u8 *)scanResult + 0xc8) & 0xff);
        }
    }
    for (i = 0; i < roomCount; i++) {
        if (rooms[i]->unk_0c == 0) {
            removeRoomPane(rooms[i]);
        }
    }
}
