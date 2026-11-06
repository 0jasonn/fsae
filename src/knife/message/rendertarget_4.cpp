#include "engine/functions.h"
#include "global.h"
#include "knife/message/message_classes.h"

// Functions in this file (original names from the debug build):
//   RenderTarget::finalize() (0x020a4e8c)
// Plain (extern "C") because rendertarget.cpp calls it by its plain name.

// RenderTarget::finalize() (0x020a4e8c): if the target is in use, clears its state block and the use flag
extern "C" void Knife_Message_RenderTarget_finalize(void *self);
void Knife_Message_RenderTarget_finalize(void *self) {
    u8 *target = (u8 *)self;

    if (target[0x1c] == 0) {
        return;
    }
    *(u32 *)(target + 0x20) = 0;
    *(u32 *)(target + 0x24) = 0;
    *(u32 *)(target + 0x28) = 0;
    *(u32 *)(target + 0x2c) = 0;
    *(u32 *)(target + 0x30) = 0;
    *(u32 *)(target + 0x34) = 0;
    *(u32 *)(target + 0x38) = 0;
    *(u32 *)(target + 0x3c) = 0;
    *(u32 *)(target + 0x40) = 0;
    *(u32 *)(target + 0x44) = 0;
    target[0x48] = 0;
    *(u32 *)(target + 0x4c) = 0;
    *(u32 *)(target + 0x50) = 0;
    *(u32 *)(target + 0x54) = 0;
    *(u32 *)(target + 0x58) = 0;
    target[0x1c] = 0;
}

// Functions in this file (original names from the debug build):
//   RenderTarget::getNumberOfUsingOBJ() const (0x020a4ee0)

extern "C" s32 func_020c61f4(s32 a, s32 b);
extern "C" void OS_Terminate(void);

namespace Knife {
namespace Message {

// RenderTarget::getNumberOfUsingOBJ() const (0x020a4ee0): the OBJ count of the target, for modes whose last digit is 4
// (anything else terminates the program)
s32 RenderTarget::getNumberOfUsingOBJ(void) const {
    if (mode % 10 == 4) {
        return func_020c61f4(unk_38, unk_3c);
    }
    OS_Terminate();
    return 0;
}

}
}
