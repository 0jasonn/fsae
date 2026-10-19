#include "engine/misc_d.h"
#include "global.h"

ARM void PaletteFade_ClearBufferFlag(void) {
    data_0216fcf8.bufferSelect = 0;
}

// Applies the fade level from the entity's x position, blends and uploads the palette buffer.
ARM void PaletteFade_Update(Entity *e) {
    u16 fadeLevel = e->x.HALF.LO;
    if (fadeLevel > 0xc0) {
        fadeLevel = 0xc0;
    }
    fadeLevel &= 0xfff8;
    if (data_0216fcf8.fadeLevel != fadeLevel) {
        Global_CopyToVram(fadeLevel << 8, fadeLevel << 8, (0x100 - fadeLevel) << 8);
        if (fadeLevel != 0) {
            Global_CopyToVram(0, 0x10000, fadeLevel << 8);
        }
        data_0216fcf8.fadeLevel = fadeLevel;
    }
    if (data_0212c5ac.blendEnabled != 0 || data_0216fcf8.fadeActive != 0) {
        switch (data_0212c5ac.blendMode) {
            case 0:
            case 2:
            case 4:
            case 5:
                Palette_BlendTowardColor(data_0212c5ac.blendColor, data_0212c5ac.blendWeight);
                break;
            case 1:
            case 3:
                Palette_BlendTowardColor(data_0212c5ac.blendColor, 0x100 - data_0212c5ac.blendWeight);
                break;
        }
    }
    data_0216fcf8.fadeActive = data_0212c5ac.blendEnabled;
    func_020152c8();
    GX_TrySetBankForLCDC(0x20);
    GX_TrySetBankForLCDC(0x40);
    MIi_CpuCopyFast(data_0216fcf8.bufferSelect != 0 ? data_0216fd04 : data_02170104, (void *)0x06896000, 0x400);
    func_02014c24(0x60);
}

ARM void PaletteFade_Init(void) {
    s32 copySize;
    void *copySource;
    func_02082c54((void *)PaletteFade_Update);
    data_0216fcf8.fadeLevel = 0xffff;
    func_020152ec();
    copySource = func_0208dde0(func_0208da4c(), &copySize, 0x3b);
    MIi_CpuCopyFast(copySource, data_0216fd04, copySize);
    MIi_CpuCopyFast(copySource, data_02170104, copySize);
    data_0216fcf8.bufferSelect = 1;
    data_0216fcf8.fadeActive = 0;
}
