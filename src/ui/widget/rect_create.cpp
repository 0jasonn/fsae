#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/rect_create.h"

extern u8 data_02126e30[];

// RectObjLink3_init (0x020b8784)
typedef struct RectObjLink3 {
    void *vtable;      // 0x00
    u8 unk_04[0x16];
    s16 unk_1a;        // 0x1a
    s16 unk_1c;        // 0x1c
    s16 unk_1e;        // 0x1e
} RectObjLink3;

void *RectObjLink3_init(RectObjLink3 *self) {
    RectObjLink2_init((void *)self);
    self->vtable = data_02126e30;
    self->unk_1a = 0;
    self->unk_1c = 0;
    self->unk_1e = 0;
    return self;
}
