#include "engine/functions.h"
#include "ui/widget/uiobj_create.h"
#include "ui/widget/rect_obj.h"

// Create helpers for the hit-test object, linked rectangle and positioned rectangle (0x020ba71c to 0x020ba7e0).
// Each one allocates its record from the heap in the first word of holder, returns NULL when the allocation fails and
// otherwise returns the object initialised in place.

void *UiObj_ba71c_create(void *holder) {
    void *obj = func_020c2c34(*(void **)holder, 0x24);
    if (obj == NULL) {
        goto null;
    }
    if (obj == NULL) {
        return obj;
    }
    return RectHitObj_init(obj);
null:
    return NULL;
}

void *RectObjLink2_create(void *holder) {
    void *obj = func_020c2c34(*(void **)holder, 0x1c);
    if (obj == NULL) {
        goto null;
    }
    if (obj == NULL) {
        return obj;
    }
    return RectObjLink2_initCopy(obj);
null:
    return NULL;
}

// Provisional name. Allocate a rectangle and initialize it from local copies of its position and size.
void *RectObj_createWithPos(void *holder, const s16 *position, const s16 *size) {
    void *obj = func_020c2c34(*(void **)holder, 0x14);

    if (obj == NULL) {
        goto null;
    }
    if (obj == NULL) {
        return obj;
    }
    {
        volatile s16 sizeCopy[2];
        volatile s16 positionCopy[2];

        sizeCopy[0] = ((volatile const s16 *)size)[0];
        sizeCopy[1] = ((volatile const s16 *)size)[1];
        positionCopy[0] = ((volatile const s16 *)position)[0];
        positionCopy[1] = ((volatile const s16 *)position)[1];
        return RectObj_initWithPos((RectObj *)obj, (const s16 *)positionCopy, (const s16 *)sizeCopy);
    }
null:
    return NULL;
}

// uiobj_create: create helpers of the small UI object types (0x020ba71c, 0x020ba748, 0x020ba7e0).
// Each one allocates its record from the heap in the first word of holder, returns NULL when the allocation fails and
// otherwise returns the object initialised in place.

void *RectSlot_create(void *holder) {
    void *obj = func_020c2c34(*(void **)holder, 0x40);
    if (obj == NULL) {
        goto null;
    }
    if (obj == NULL) {
        return obj;
    }
    return RectSlot_init(obj);
null:
    return NULL;
}
