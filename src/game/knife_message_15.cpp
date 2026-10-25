#include "engine/functions.h"
#include "global.h"

// Functions in this file (invented name, the debug build has none):
//   MessageTextRender::onReadNop (0x020a0898): an empty tag handler

// MessageTextRender::onReadNop() (0x020a0898): an empty tag handler
extern "C" void Knife_Message_MessageTextRender_onReadNop(void *a);
ARM void Knife_Message_MessageTextRender_onReadNop(void *a) {
}
