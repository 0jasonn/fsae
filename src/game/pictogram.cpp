#include "engine/functions.h"
#include "global.h"
#include "game/pictogram.h"

// Functions in this file (original names from the debug build):
//   PictogramRenderer::~PictogramRenderer() (0x020a48d0, deleting), assignOam (0x020a48e4), setCharInfo (0x020a4904),
//   clearAllPictogram (0x020a4928), clearPictogram (0x020a4968)

extern "C" void MI_CpuCopy8(const void *src, void *dst, u32 size);

namespace Knife {
namespace Message {

// PictogramRenderer::~PictogramRenderer() (0x020a48d0): the deleting destructor, the empty base destructor is inlined
extern "C" void *Knife_Message_PictogramRenderer_dtor_PictogramRenderer(void *self);
ARM void *Knife_Message_PictogramRenderer_dtor_PictogramRenderer(void *self) {
    operator delete(self);
    return self;
}

// PictogramRenderer::assignOam(GXOamAttr*, int) (0x020a48e4): stores the OAM buffer and the count (0 to 0x80), then clears
ARM void PictogramRenderer::assignOam(GXOamAttr *oamBuf, s32 pictCount) {
    if (pictCount < 0) {
        pictCount = 0;
    }
    if (pictCount > 0x80) {
        pictCount = 0x80;
    }
    oam = oamBuf;
    count = pictCount;
    clearAllPictogram();
}

// PictogramRenderer::setCharInfo(PictCharInfo const*) (0x020a4904): copies the character info, then clears
ARM void PictogramRenderer::setCharInfo(const PictCharInfo *info) {
    MI_CpuCopy8(info, &charInfo, sizeof(PictCharInfo));
    clearAllPictogram();
}

// PictogramRenderer::clearAllPictogram() (0x020a4928): clears every pictogram of the buffer
ARM void PictogramRenderer::clearAllPictogram(void) {
    s32 i;

    if (oam == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        clearPictogram(i);
    }
}

// PictogramRenderer::clearPictogram(int) (0x020a4968): hides the OAM entry and clears its used bit
ARM void PictogramRenderer::clearPictogram(s32 index) {
    u32 *attr;

    if (oam == NULL) {
        return;
    }
    attr = (u32 *)&oam[index];
    *attr = (*attr & 0xc1fffcff) | 0x200;
    usedBits[index / 32] &= ~(1u << (index % 32));
}

}
}
