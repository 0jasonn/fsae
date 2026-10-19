#include "engine/functions.h"
#include "engine/misc_d.h"
#include "global.h"

ARM void PaletteFade_ClearBufferFlag(void) {
    paletteFade.bufferSelect = 0;
}

// Applies the fade level from the entity's x position, blends and uploads the palette buffer.
ARM void title_resourceCtrlCallback(DISP_CTRL_ *ctrl) {
    Entity *e = (Entity *)ctrl; // DISP_CTRL_ layout not known yet; read through the Entity view
    u16 fadeLevel = e->x.HALF.LO;
    if (fadeLevel > 0xc0) {
        fadeLevel = 0xc0;
    }
    fadeLevel &= 0xfff8;
    if (paletteFade.fadeLevel != fadeLevel) {
        refreshVirtualScreenData(fadeLevel << 8, fadeLevel << 8, (0x100 - fadeLevel) << 8);
        if (fadeLevel != 0) {
            refreshVirtualScreenData(0, 0x10000, fadeLevel << 8);
        }
        paletteFade.fadeLevel = fadeLevel;
    }
    if (data_0212c5ac.blendEnabled != 0 || paletteFade.fadeActive != 0) {
        switch (data_0212c5ac.blendMode) {
            case 0:
            case 2:
            case 4:
            case 5:
                title_MakeFadeBuff256(data_0212c5ac.blendColor, data_0212c5ac.blendWeight);
                break;
            case 1:
            case 3:
                title_MakeFadeBuff256(data_0212c5ac.blendColor, 0x100 - data_0212c5ac.blendWeight);
                break;
        }
    }
    paletteFade.fadeActive = data_0212c5ac.blendEnabled;
    func_020152c8();
    GX_TrySetBankForLCDC(0x20);
    GX_TrySetBankForLCDC(0x40);
    MIi_CpuCopyFast(paletteFade.bufferSelect != 0 ? data_0216fd04 : data_02170104, (void *)0x06896000, 0x400);
    func_02014c24(0x60);
}

ARM void setupVirtualScreenCallback(void) {
    s32 copySize;
    void *copySource;
    func_02082c54((void *)title_resourceCtrlCallback);
    paletteFade.fadeLevel = 0xffff;
    func_020152ec();
    copySource = KnifeApp_getZeldaResource_08dde0(KnifeApp_getInstance(), &copySize, 0x3b);
    MIi_CpuCopyFast(copySource, data_0216fd04, copySize);
    MIi_CpuCopyFast(copySource, data_02170104, copySize);
    paletteFade.bufferSelect = 1;
    paletteFade.fadeActive = 0;
}
