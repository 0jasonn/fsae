#include "engine/functions.h"
#include "ui/widget/rect_create_2.h"

// rect_create: the three create helpers of the rect object family.
//   RectObjList_create (0x020b8528, 0x1c bytes)
//   RectObjLink_create (0x020b88b0, 0x1c bytes)
//   RectSlot2_create   (0x020b9258, 0x2c bytes)
// Each one allocates its record from the heap in the first word of holder, returns NULL when the allocation fails and
// otherwise returns the object initialised in place. The explicit null-return block after the call is what keeps the
// compiler from folding the check into a conditional move.

void *RectObjList_create(void *holder) {
    void *obj = func_020c2c34(*(void **)holder, 0x1c);
    if (obj == NULL) {
        goto null;
    }
    if (obj == NULL) {
        return obj;
    }
    return RectObjList_init2(obj);
null:
    return NULL;
}

