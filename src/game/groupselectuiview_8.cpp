#include "engine/functions.h"
#include "global.h"
#include "game/uiobject.h"
#include "game/groupselectuiview.h"

// Functions in this file (original names from the debug build):
//   groupSelectUIView::removeRoomPane (0x020b0b40)

// groupSelectUIView::removeRoomPane (0x020b0b40): removes a room from the list and moves the rooms behind it up one row
ARM void groupSelectUIView::removeRoomPane(RoomInfo *room) {
    u32 i;
    u32 found;
    RoomInfo *moved;

    found = 0xffffffff;
    for (i = 0; i < roomCount; i++) {
        if (rooms[i] == room) {
            found = i;
            room->active = 0;
            room->unk_0c = 0;
            SoundReq(0x44);
            break;
        }
    }
    if (found == 0xffffffff) {
        return;
    }
    for (i = found; i < roomCount - 1; i++) {
        moved = rooms[i + 1];
        rooms[i] = moved;
        data_0217eb2c[moved->uiIndex].durationFP = 0;
        data_0217eb2c[moved->uiIndex].pos.x = 0x80000;
        data_0217eb2c[moved->uiIndex].pos.y = (i * 0x28 + 0x30) << 12;
        writeOamBuffer(moved, i);
    }
    roomCount--;
}
