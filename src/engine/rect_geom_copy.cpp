#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_f.h"

// rect_geom_copy: function RectObjList_setGeometryCopy (0x020bba38), provisional name.

// RectObjList_setGeometryCopy(self, pos, size, value, a20, a24) (0x020bba38, provisional name): copies the size and the
// position (two halfwords each) into locals, calls RectObjList_setGeometry with them and value, then stores a20 at +0x20
// and a24 at +0x24. The last two arguments are on the stack.
extern "C" void RectObjList_setGeometryCopy(void *self, s16 *pos, s16 *size, s32 value, s32 a20, s32 a24);
ARM void RectObjList_setGeometryCopy(void *self, s16 *pos, s16 *size, s32 value, s32 a20, s32 a24) {
    s16 posCopy[2];
    s16 sizeCopy[2];

    sizeCopy[0] = size[0];
    sizeCopy[1] = size[1];
    posCopy[0] = pos[0];
    posCopy[1] = pos[1];
    RectObjList_setGeometry(self, posCopy, sizeCopy, value);
    ((s32 *)self)[0x20 / 4] = a20;
    ((s32 *)self)[0x24 / 4] = a24;
}
