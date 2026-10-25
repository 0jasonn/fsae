#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_obj_f.h"

// rect_pair: functions RectObjPair_setHitFlags (0x020b86b8), RectObjPair_updateFlags (0x020b86f4) and
// RectObjPair_countDownBoth (0x020b8760). The pair keeps its two children at +0x14 (child 0 at +0, child 1 at +4).

// Child of a pair: the RectObjF fields, the flag byte as bits (RectFlagBits) at +0x10
typedef struct RectPairChild {
    void *vtable;          // 0x00
    u8 unk_04[0xc];
    RectFlagBits flags;    // 0x10
} RectPairChild;

// Pair of children (see rect_item.cpp for the fields at +0x14 to +0x1e)
typedef struct RectPair {
    u8 unk_00[0x14];
    RectPairChild **children; // 0x14
    u8 unk_18[2];
    s16 limit;             // 0x1a
    s16 offset;            // 0x1c
    s16 value;             // 0x1e
    s16 unk_20;            // 0x20
} RectPair;

extern "C" void RectObjList_countDown(void *self);

// RectObjPair_setHitFlags(self, first, second) (0x020b86b8, provisional name): the hit bit of child 1 is set from first
// and the hit bit of child 0 from second (bit 0 of each argument)
extern "C" void RectObjPair_setHitFlags(RectPair *self, u8 first, u8 second);
ARM void RectObjPair_setHitFlags(RectPair *self, u8 first, u8 second) {
    RectPairChild *child;

    child = self->children[1];
    child->flags.hit = first;
    child = self->children[0];
    child->flags.hit = second;
}

// RectObjPair_updateFlags(self, value) (0x020b86f4, provisional name): stores value at +0x20, then the unk_bit1 bit of
// child 1 is set when value is not positive and the one of child 0 when value + value at +0x1e is at least the limit
extern "C" void RectObjPair_updateFlags(RectPair *self, s32 value);
ARM void RectObjPair_updateFlags(RectPair *self, s32 value) {
    RectPairChild *child;

    self->unk_20 = value;
    child = self->children[1];
    child->flags.unk_bit1 = (self->unk_20 <= 0);
    child = self->children[0];
    child->flags.unk_bit1 = (self->unk_20 + self->value >= self->offset);
}

// RectObjPair_countDownBoth(self) (0x020b8760, provisional name): counts down both children (child 1 first)
extern "C" void RectObjPair_countDownBoth(RectPair *self);
ARM void RectObjPair_countDownBoth(RectPair *self) {
    RectObjList_countDown(self->children[1]);
    RectObjList_countDown(self->children[0]);
}
