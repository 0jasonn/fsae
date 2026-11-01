#include "engine/functions.h"
#include "global.h"
#include "knife/message/pictogram_noop_api.h"
#include "knife/message/rendertarget_api.h"

// Functions in this file (original names from the debug build, or invented where marked):
//   i_IsExText (0x020a3134), RenderTarget::~RenderTarget() (0x020a3160, deleting), Knife_Message_i_FinalizeRenderTargets (name invented)

extern u8 data_02124984[];  // RenderTarget vtable
extern u8 data_0217d56c[];  // render target pool: the array pointer is at +0x0c
extern u8 data_0217d650[];  // render target array, 0x208 bytes per entry, 2 entries
extern "C" void Knife_Message_RenderTarget_finalize(void *self);
extern "C" void Frame_LoopC868(void *array, s32 count, u32 size, void *dtor);

// i_IsExText(unsigned long) (0x020a3134): true for the character codes 0x2328 to 0x270f
extern "C" BOOL Knife_Message_i_IsExText(u32 code);
BOOL Knife_Message_i_IsExText(u32 code) {
    if (code >= 0x2328 && code <= 0x270f) {
        return 1;
    }
    return 0;
}

// RenderTarget::~RenderTarget() (0x020a3160): the deleting destructor, as 0x020a2dd4 and then operator delete
void *Knife_Message_RenderTarget_dtor_RenderTarget_0a3160(void *self) {
    *(u8 **)self = data_02124984;
    Knife_Message_RenderTarget_finalize(self);
    operator delete(self);
    return self;
}

// Knife_Message_i_FinalizeRenderTargets (name invented): destroys the two render targets of data_0217d650
void Knife_Message_i_FinalizeRenderTargets(void) {
    Frame_LoopC868(data_0217d650, 2, 0x208, (void *)Knife_Message_PictogramRenderer_noop);
}
