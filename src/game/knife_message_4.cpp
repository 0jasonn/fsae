#include "engine/functions.h"
#include "global.h"
#include "game/knife_message.h"

// Functions in this file (original names from the debug build, or guessed where the debug build has none):
//   MessageTextRender::onReadWaitTag (0x020a0814), setOffset (0x020a082c), setSceneField_dc (0x020a0838)

namespace Knife {
namespace Message {

// MessageTextRender::onReadWaitTag(int) (0x020a0814): a wait value of 0xff sets the wait flag, others are stored as the count
ARM void MessageTextRender::onReadWaitTag(int value) {
    if (value == 0xff) {
        sceneInfo->waitFlag = 1;
    } else {
        sceneInfo->waitCount = value;
    }
}

// MessageTextRender::setOffset (0x020a082c): stores the x and y offsets of the text
ARM void MessageTextRender::setOffset(s16 x, s16 y) {
    offsetX = x;
    offsetY = y;
}

// MessageTextRender::setSceneField_dc (0x020a0838): stores the byte at +0xdc of the scene block
ARM void MessageTextRender::setSceneField_dc(u8 value) {
    sceneInfo->field_dc = value;
}

}
}
