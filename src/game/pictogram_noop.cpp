#include "engine/functions.h"
#include "global.h"

// Functions in this file (invented name, the debug build has none):
//   Knife_Message_PictogramRenderer_noop: an empty function before PictogramRenderer::dtor

// PictogramRenderer::noop() (0x020a48cc): does nothing
extern "C" void Knife_Message_PictogramRenderer_noop(void *a);
ARM void Knife_Message_PictogramRenderer_noop(void *a) {
}
