#include "engine/functions.h"
#include "global.h"
#include "game/uiobject.h"
#include "game/groupselectuiview.h"

// Functions in this file (original names from the debug build):
//   groupSelectUIView::stopScan (0x020b0fe8), getText (0x020b0ff8), getRoomInfoFromTextID (0x020b108c),
//   noop (0x020b10d0, renamed from groupSelectUIView_noop)

// groupSelectUIView::stopScan (0x020b0fe8): stops the wireless scan
ARM void groupSelectUIView::stopScan(void) {
    void *manager;

    manager = func_020909c8();
    func_02091464(manager);
}

// groupSelectUIView::getText (0x020b0ff8): fills the text handle of a room (or of the not-found message)
ARM BOOL groupSelectUIView::getText(KnifeMsgText *text, u32 textId, s32 language) {
    RoomInfo *room;
    const void *arg;
    const u16 *str;
    s32 index;

    room = getRoomInfoFromTextID(textId);
    if (room == NULL) {
        arg = *(const u16 **)(data_021263cc + 0x10);
        text->str = (const u16 *)arg;
        text->kind = 6;
    } else if ((textId - 0x2328) & 1) {
        index = (s32)room->nameIndex - 1;
        if (index < 0) {
            index = 0;
        }
        if (index > 3) {
            index = 3;
        }
        str = ((const u16 **)data_021263dc)[index];
        arg = (const void *)6;
        text->kind = 6;
        text->str = str;
    } else {
        arg = (const void *)0xc;
        text->str = room->name;
        text->kind = 0xc;
    }
    text->handle = func_0208fc6c(arg);
    return TRUE;
}

// groupSelectUIView::getRoomInfoFromTextID (0x020b108c): the room slot that owns a text pane, NULL if none does
ARM groupSelectUIView::RoomInfo *groupSelectUIView::getRoomInfoFromTextID(u32 textId) {
    u32 i;
    u32 pane;

    pane = textId - 0x2328;
    for (i = 0; i < 4; i++) {
        if (pane == slots[i].paneNo || pane == slots[i].paneNo + 1) {
            return &slots[i];
        }
    }
    return NULL;
}

// groupSelectUIView::noop (0x020b10d0): empty
ARM void groupSelectUIView::noop(void) {
}
