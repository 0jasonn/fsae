#include "engine/functions.h"
#include "global.h"
#include "game/knife_message.h"

// Functions in this file (names guessed from the stored field, the debug build has none):
//   MessageTextRender::clearField36 (0x020a0624), getField36 (0x020a0630), setSceneInfo (0x020a0638)

namespace Knife {
namespace Message {

// MessageTextRender::clearField36 (0x020a0624): clears the byte at +0x36
ARM void MessageTextRender::clearField36(void) {
    field36 = 0;
}

// MessageTextRender::getField36 (0x020a0630): reads the byte at +0x36
ARM u8 MessageTextRender::getField36(void) const {
    return field36;
}

// MessageTextRender::setSceneInfo (0x020a0638): stores the scene block pointer at +0x38
ARM void MessageTextRender::setSceneInfo(void *info) {
    sceneInfo = (MessageSceneInfo *)info;
}

}
}
