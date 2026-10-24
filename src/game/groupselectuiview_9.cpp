#include "engine/functions.h"
#include "global.h"
#include "game/uiobject.h"
#include "game/groupselectuiview.h"

// Functions in this file (original names from the debug build):
//   groupSelectUIView::addRoomPane (0x020b0800)

// groupSelectUIView::addRoomPane (0x020b0800): updates the room with the same id, or takes the first free slot for a
// new room (copies its name, draws it and appends it to the list), then sorts the list
ARM void groupSelectUIView::addRoomPane(const u8 *id, const u16 *name, u32 nameBytes, u8 nameIndex, u32 sortKey) {
    RoomUiIndexTable uiIndex;
    RoomInfo *room;
    RoomInfo *slot;
    u32 i;
    u32 index;
    BOOL same;

    uiIndex = data_020ded24;
    for (i = 0; i < roomCount; i++) {
        room = rooms[i];
        same = room->id[0] == id[0] && room->id[1] == id[1] && room->id[2] == id[2] && room->id[3] == id[3] &&
            room->id[4] == id[4] && room->id[5] == id[5];
        if (same) {
            room->sortKey = sortKey;
            room->unk_0c = 1;
            room->state++;
            if (room->nameIndex != nameIndex) {
                room->nameIndex = nameIndex;
                redrawText(room, i);
            }
            return;
        }
    }
    for (i = 0; i < 4; i++) {
        if (slots[i].active == 0) {
            slot = &slots[i];
            slot->active = 1;
            slot->id[0] = id[0];
            slot->id[1] = id[1];
            slot->id[2] = id[2];
            slot->id[3] = id[3];
            slot->id[4] = id[4];
            slot->id[5] = id[5];
            MI_CpuFill8(slot->name, 0, 0xe);
            MI_CpuCopy8(name, slot->name, nameBytes);
            slot->nameIndex = nameIndex;
            slot->sortKey = sortKey;
            slot->uiIndex = uiIndex.uiIndex[i];
            slot->unk_0b = 0;
            slot->paneNo = i * 2;
            slot->unk_0c = 1;
            slot->state = 0;
            redrawText(slot, roomCount);
            index = roomCount;
            roomCount = index + 1;
            rooms[index] = slot;
            SoundReq(0x43);
            roomSort();
            return;
        }
    }
}
