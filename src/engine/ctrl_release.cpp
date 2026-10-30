#include "engine/functions.h"
#include "global.h"
#include "types.h"

// ctrl_release: function Ctrl_releaseSubobjects (0x020ba80c), provisional name.

extern "C" void RectObj_noop(void *self, s32 arg);

// Subobject with one virtual slot (declared only, never constructed, so no vtable is emitted here)
class CtrlSubobject {
public:
    virtual void release(s32 arg);
};

// Controller record with two embedded subobjects, at +0x20 and +0x3c
typedef struct CtrlRelease {
    u8 unk_00[0x20];
    u8 subB[0x1c];     // 0x20: subobject B, its vtable pointer is the first word
    u8 unk_3c[0x4];    // 0x3c: subobject A starts here
} CtrlRelease;

// Ctrl_releaseSubobjects(self, arg) (0x020ba80c, provisional name): calls the first virtual of subobject A (+0x3c) and
// of subobject B (+0x20) with arg, then RectObj_noop(self, arg)
extern "C" void Ctrl_releaseSubobjects(void *selfv, s32 arg);
ARM void Ctrl_releaseSubobjects(void *selfv, s32 arg) {
    CtrlRelease *self = (CtrlRelease *)selfv;
    ((CtrlSubobject *)self->unk_3c)->release(arg);
    ((CtrlSubobject *)self->subB)->release(arg);
    RectObj_noop(self, arg);
}
