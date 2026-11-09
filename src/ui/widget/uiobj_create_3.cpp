#include "engine/functions.h"
#include "ui/widget/uiobj_create.h"

// uiobj_create: create helpers of the small UI object types (0x020ba71c, 0x020ba748, 0x020ba7e0).
// Each one allocates its record from the heap in the first word of holder, returns NULL when the allocation fails and
// otherwise returns the object initialised in place.

void *UiObj_ba7e0_create(void *holder) {
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
