#include "engine/functions.h"
#include "ui/widget/uiobj_create.h"

// uiobj_create: create helpers of the small UI object types (0x020ba71c, 0x020ba748, 0x020ba7e0).
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
    return func_020b8408(obj);
null:
    return NULL;
}

void *UiObj_ba748_create(void *holder) {
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

