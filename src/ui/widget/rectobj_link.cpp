#include "engine/functions.h"
#include "ui/widget/rectobj_link.h"

// RectObjLink_callA (0x020b7fec): forwards the call to Table_setValueB with the value stored at +0x14 of the object.

typedef struct RectObjLink {
    u8 unk_00[0x14];
    void *value14;     // 0x14
} RectObjLink;

void RectObjLink_callA(void *selfv, void *ctx, s32 arg) {
    RectObjLink *self = (RectObjLink *)selfv;

    Table_setValueB(ctx, self->value14, arg);
}
