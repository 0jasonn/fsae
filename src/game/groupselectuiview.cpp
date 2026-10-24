#include "engine/functions.h"
#include "global.h"
#include "game/uiobject.h"
#include "game/groupselectuiview.h"

// Functions in this file (original names from the debug build):
//   groupSelectUIView::moveOutRoom (0x020afef4), moveReturnRoom (0x020aff84)

// groupSelectUIView::moveOutRoom (0x020afef4): every room slides to x = -128 and is redrawn at its new position
ARM void groupSelectUIView::moveOutRoom(void) {
    u32 i;
    UIObject *obj;

    for (i = 0; i < roomCount; i++) {
        obj = &data_0217eb2c[rooms[i]->uiIndex];
        UIObject_movePos(obj, -0x80000, obj->pos.y & -0x1000, data_020de848, ANIMATION_CURVE_EASE_IN);
        writeOamBuffer(rooms[i], i);
    }
}

// groupSelectUIView::moveReturnRoom (0x020aff84): every room slides to x = 384 and is redrawn at its new position
ARM void groupSelectUIView::moveReturnRoom(void) {
    u32 i;
    UIObject *obj;

    for (i = 0; i < roomCount; i++) {
        obj = &data_0217eb2c[rooms[i]->uiIndex];
        UIObject_movePos(obj, 0x180000, obj->pos.y & -0x1000, data_020de848, ANIMATION_CURVE_EASE_IN);
        writeOamBuffer(rooms[i], i);
    }
}
