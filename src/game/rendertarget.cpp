#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   RenderTarget::~RenderTarget() (0x020a2dd4, base destructor)

extern u8 data_02124984[];  // RenderTarget vtable
extern u8 data_0217d56c[];  // render target pool: the array pointer is at +0x0c
extern u8 data_0217d650[];  // render target array, 0x208 bytes per entry, 2 entries
extern "C" void Knife_Message_RenderTarget_finalize(void *self);
extern "C" void func_020a48cc(void *self);
extern "C" void func_0200c868(void *array, s32 count, u32 size, void *dtor);

// RenderTarget::~RenderTarget() (0x020a2dd4): sets the vtable, finalizes and returns the object
extern "C" void *Knife_Message_RenderTarget_dtor_RenderTarget_0a2dd4(void *self);
ARM void *Knife_Message_RenderTarget_dtor_RenderTarget_0a2dd4(void *self) {
    *(u8 **)self = data_02124984;
    Knife_Message_RenderTarget_finalize(self);
    return self;
}
