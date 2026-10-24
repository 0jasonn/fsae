#include "engine/functions.h"
#include "global.h"
#include "game/knife_message.h"

// Functions in this file (original names from the debug build):
//   Knife::Message::MessageTextRender::clearCanvasLine (0x0209fcdc + 0x020a0508 range; this is 0x020a0508)

namespace Knife {
namespace Message {

// MessageTextRender::clearCanvasLine(long, long, long) (0x020a0508): fills cells of the canvas with a colour
ARM void MessageTextRender::clearCanvasLine(s32 line, s32 lines, s32 color) {
    u32 spread = SpreadColor32(&canvas, color);
    u8 *dst = (u8 *)canvas.pBits + line * canvas.width * Knife_CharBytes(&canvas);
    s32 size = canvas.width * lines * Knife_CharBytes(&canvas);

    MIi_CpuClearFast(spread, dst, size);
}

}
}
