#include "engine/functions.h"
#include "global.h"
#include "game/knife_message.h"

// Functions in this file (original names from the debug build):
//   MessageTextRender::onReadBlankTag (0x020a0dac)

namespace Knife {
namespace Message {

// MessageTextRender::onReadBlankTag(int) (0x020a0dac): moves the text x position by a blank of value pixels
ARM void MessageTextRender::onReadBlankTag(int value) {
    offsetX = offsetX + (s16)value;
}

}
}
