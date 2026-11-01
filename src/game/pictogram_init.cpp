#include "engine/functions.h"
#include "game/pictogram_init.h"

extern u8 data_0212499c[]; // vtable of the global pictogram block

// Static initializer (0x020a4888): sets the vtable, clears the count and the character info table (0x1ec bytes at
// +0x0c) and the used bits (0x10 bytes at +0x1f8). Returns self.
void *Knife_Message_PictogramRenderer_initGlobal(void *self) {
    *(void **)self = data_0212499c;
    *(u32 *)((u8 *)self + 0x04) = 0;
    *(u32 *)((u8 *)self + 0x08) = 0;
    MI_CpuFill8((u8 *)self + 0x0c, 0, 0x1ec);
    MI_CpuFill8((u8 *)self + 0x1f8, 0, 0x10);
    return self;
}
