#include "engine/functions.h"
#include "global.h"
#include "game/message_e.h"

// Functions in this file (original names from the debug build):
//   TextRenderer::clearCanvas (0x020a58b4)

namespace Knife {
namespace Message {

// TextRenderer::clearCanvas(unsigned char) (0x020a58b4): calls the clear function stored at +4 of the object at target+0x18,
// with target+4 as its first argument
ARM void TextRenderer::clearCanvas(u8 value) {
    void *canvas = *(void **)((u8 *)target + 0x18);
    void (*clearFunc)(void *, u8) = *(void (**)(void *, u8))((u8 *)canvas + 4);

    clearFunc((u8 *)target + 4, value);
}

}
}
