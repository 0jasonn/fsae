#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   GetRenderTarget(int) (0x020a2efc)

extern u8 data_02124984[];  // RenderTarget vtable
extern u8 data_0217d56c[];  // render target pool: the array pointer is at +0x0c
extern u8 data_0217d650[];  // render target array, 0x208 bytes per entry, 2 entries
extern "C" void Knife_Message_RenderTarget_finalize(void *self);
extern "C" void func_020a48cc(void *self);
extern "C" void func_0200c868(void *array, s32 count, u32 size, void *dtor);

// RenderTarget::GetRenderTarget(int) (0x020a2efc): the entry of the pool, or NULL while the pool is empty
extern "C" void *Knife_Message_GetRenderTarget(s32 index);
ARM void *Knife_Message_GetRenderTarget(s32 index) {
    u8 *base = *(u8 **)(data_0217d56c + 0xc);

    if (base == NULL) {
        return NULL;
    }
    return base + index * 0x68;
}
