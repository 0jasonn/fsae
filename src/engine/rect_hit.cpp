#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_obj_f.h"

// rect_hit: function RectObjList_findHit (0x020b8398), matching.

extern "C" BOOL RectObj_hitTest(void *self, s16 *pos);

// RectObjList_findHit(items, count, pos) (0x020b8398, provisional name): index of the first item that RectObj_hitTest
// (RectObj_hitTest) accepts at pos, or -1 when none does
extern "C" s32 RectObjList_findHit(void **items, s32 count, s16 *pos);
ARM s32 RectObjList_findHit(void **items, s32 count, s16 *pos) {
    s16 point[2];
    s16 i;

    for (i = 0; i < count; i++) {
        point[0] = pos[0];
        point[1] = pos[1];
        if (RectObj_hitTest(items[i], point) != FALSE) {
            return i;
        }
    }
    return -1;
}

