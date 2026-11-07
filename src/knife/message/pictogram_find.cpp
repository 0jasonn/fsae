#include "engine/functions.h"
#include "global.h"
#include "knife/message/pictogram.h"
#include "engine/clz.h"

// Functions in this file (original names from the debug build):
//   Knife::Message::PictogramRenderer::findEmptyIndex() const (0x020a4a80)

namespace Knife {
namespace Message {

// PictogramRenderer::findEmptyIndex() const (0x020a4a80): index of the first pictogram whose used bit is clear
// (the lowest clear bit of the first word that is not full), or -1 when all are used
s32 PictogramRenderer::findEmptyIndex(void) const {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (usedBits[i] != 0xffffffff) {
            u32 inv = ~usedBits[i];

            return 32 - CountLeadingZeros(~inv & (inv - 1)) + i * 32;
        }
    }
    return -1;
}

}
}
