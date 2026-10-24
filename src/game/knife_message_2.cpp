#include "engine/functions.h"
#include "global.h"
#include "game/knife_message.h"

// Functions in this file (original names from the debug build, or guessed where the debug build has none):
//   MessageTextRender::setField34 (0x020a056c), setField35 (0x020a0564) (names guessed from the stored byte)
// Fields 0x34..0x38 of MessageTextRender are not known yet, so the setters only name the slot.

namespace Knife {
namespace Message {

// MessageTextRender::setField35 (0x020a0564): stores the byte at +0x35
ARM void MessageTextRender::setField35(u8 value) {
    field35 = value;
}

// MessageTextRender::setField34 (0x020a056c): stores the byte at +0x34
ARM void MessageTextRender::setField34(u8 value) {
    field34 = value;
}

}
}
