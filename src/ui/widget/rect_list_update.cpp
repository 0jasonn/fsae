#include "types.h"
#include "ui/widget/rect_list.h"
#include "ui/widget/rect_obj_view.h"

struct RectBufTable;

extern "C" BOOL RectObj_updateBoundsCheck(RectObjF *self, const s16 *pos);
extern "C" s32 Table_setValueB(u8 *owner, s32 index, s32 kind);
extern "C" BOOL RectBufTable_setup(RectBufTable *owner, s32 index, s32 x, s32 y);

// Provisional parameter types follow the shared rect-list layout. Bounds are passed as 20.12 coordinates.
extern "C" void func_020b82f4(RectObjList *self, void **owner, s16 *pos);
void func_020b82f4(RectObjList *self, void **owner, s16 *pos) {
    s16 checkPos[2];
    s32 kind;

    checkPos[0] = pos[0];
    checkPos[1] = pos[1];
    if (RectObj_updateBoundsCheck((RectObjF *)self, checkPos) == FALSE) {
        return;
    }
    kind = 0;
    if (self->count != 0) {
        kind = 1;
    } else {
        RectFlagBits *flags = (RectFlagBits *)&self->flags;
        if (flags->unk_bit1) {
            goto kindTwo;
        }
        if (flags->hit) {
            kind = 1;
        }
        goto setupCalls;
    kindTwo:
        kind = 2;
    }
setupCalls:
    Table_setValueB((u8 *)*owner, (s32)self->field14, kind);
    RectBufTable_setup((RectBufTable *)*owner, (s32)self->field14, self->boundX * 0x1000, self->boundY * 0x1000);
}
