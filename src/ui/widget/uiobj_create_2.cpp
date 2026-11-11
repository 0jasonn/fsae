#include "engine/functions.h"
#include "ui/widget/uiobj_create.h"
#include "ui/widget/rect_create_2.h"

// uiobj_create_2: the remaining create helpers of the UI object types in the menu/cursor families
// (0x020bcd34, 0x020bcd60, 0x020bcd8c, 0x020bcdb8, 0x020bcde4, 0x020be128).
// Each one allocates its record from the heap in the first word of holder, returns NULL when the allocation fails and
// otherwise returns the object initialised in place.

void *CtrlItem_create(void *holder) {
    void *obj = func_020c2c34(*(void **)holder, 0xb0);
    if (obj == NULL) {
        goto null;
    }
    if (obj == NULL) {
        return obj;
    }
    return CtrlItem_init(obj);
null:
    return NULL;
}

void *LobbyMsgObj_create(void *holder) {
    void *obj = func_020c2c34(*(void **)holder, 0x20);
    if (obj == NULL) {
        goto null;
    }
    if (obj == NULL) {
        return obj;
    }
    return lobby_msgObj_init(obj);
null:
    return NULL;
}

void *RectObjLink3_create(void *holder) {
    void *obj = func_020c2c34(*(void **)holder, 0x24);
    if (obj == NULL) {
        goto null;
    }
    if (obj == NULL) {
        return obj;
    }
    return RectObjLink3_init((RectObjLink3 *)obj);
null:
    return NULL;
}

void *RectSlot3_create(void *holder) {
    void *obj = func_020c2c34(*(void **)holder, 0x24);
    if (obj == NULL) {
        goto null;
    }
    if (obj == NULL) {
        return obj;
    }
    return RectSlot3_init(obj);
null:
    return NULL;
}

void *UiObj_bcde4_create(void *holder) {
    void *obj = func_020c2c34(*(void **)holder, 0x3034);
    if (obj == NULL) {
        goto null;
    }
    if (obj == NULL) {
        return obj;
    }
    return func_020bbf54(obj);
null:
    return NULL;
}

