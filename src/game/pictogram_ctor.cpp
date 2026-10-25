#include "engine/functions.h"
#include "global.h"

// Functions in this file (invented name, the debug build has none):
//   Knife_Message_PictogramRenderer_PictogramRenderer: PictogramRenderer constructor (sets the vtable, clears the flag at +0x1c)

extern u8 data_02124984[]; // vtable of PictogramRenderer

// PictogramRenderer::PictogramRenderer() (0x020a4ad8): sets the vtable and clears the flag at +0x1c
extern "C" void *Knife_Message_PictogramRenderer_PictogramRenderer(void *self);
ARM void *Knife_Message_PictogramRenderer_PictogramRenderer(void *self) {
    *(void **)self = data_02124984;
    ((u8 *)self)[0x1c] = 0;
    return self;
}
