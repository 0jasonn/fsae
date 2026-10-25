#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   RenderTarget::finalize() (0x020a4e8c)
// Plain (extern "C") because rendertarget.cpp calls it by its plain name.

// RenderTarget::finalize() (0x020a4e8c): if the target is in use, clears its state block and the use flag
extern "C" void Knife_Message_RenderTarget_finalize(void *self);
ARM void Knife_Message_RenderTarget_finalize(void *self) {
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
