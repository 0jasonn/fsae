#include "engine/functions.h"
#include "global.h"

// Functions in this file (invented name, the debug build has none):
//   TextRender::onReadNop (0x020a1390): an empty tag handler

// TextRender::onReadNop() (0x020a1390): an empty tag handler
extern "C" void Knife_Message_TextRender_onReadNop(void *a);
ARM void Knife_Message_TextRender_onReadNop(void *a) {
}
