#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"
#include "game/uiobject.h"
#include "game/groupselectuiview.h"

// Functions in this file (original names from the debug build):
//   groupSelectUIView::writeOamBuffer (0x020b0a6c)

// groupSelectUIView::writeOamBuffer (0x020b0a6c): writes the OAM cells of the two panes of a room at its position
void groupSelectUIView::writeOamBuffer(RoomInfo *room, s32 index) {
    TextRenderTarget *target;
    UIObject *obj;

    target = (TextRenderTarget *)Knife_Message_GetRenderTarget(room->paneNo);
    obj = &data_0217eb2c[room->uiIndex];
    func_020c6550(target->cellBase + (target->cellIndex << 3), target->unk_38, target->unk_3c,
                  ((s32 *)data_021263cc)[0] + (obj->pos.x >> 12), ((s32 *)data_021263cc)[1] + (obj->pos.y >> 12), 0, target->unk_2c);
    target = (TextRenderTarget *)Knife_Message_GetRenderTarget(room->paneNo + 1);
    obj = &data_0217eb2c[room->uiIndex];
    func_020c6550(target->cellBase + (target->cellIndex << 3), target->unk_38, target->unk_3c,
                  ((s32 *)data_021263cc)[2] + (obj->pos.x >> 12), ((s32 *)data_021263cc)[3] + (obj->pos.y >> 12), 0, target->unk_2c);
}

// Functions in this file (original names from the debug build):
//   groupSelectUIView::removeRoomPane (0x020b0b40)

// groupSelectUIView::removeRoomPane (0x020b0b40): removes a room from the list and moves the rooms behind it up one row
void groupSelectUIView::removeRoomPane(RoomInfo *room) {
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
