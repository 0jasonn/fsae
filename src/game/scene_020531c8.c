#include "game/scene_d.h"
#include "global.h"

// Scene_ResetPaletteA -> Scene_ResetPaletteA
// Scene_ResetPaletteB -> Scene_ResetPaletteB
// Scene_LoadBackground -> Scene_LoadBackground
// Scene_FlushDirtyTiles -> Scene_FlushDirtyTiles
// Region of the tile map to flush is data_0216fcf8 bytes [4..7]: x, y, width, height (tiles).
ARM void Scene_ResetPaletteA(void) {
    if (data_0212c5ac.blendEnabled != 0) {
        return;
    }
    func_0202a60c();
    *(u16 *)0x05000000 = 0x6739;
    *(u16 *)&data_021355a0 = 0x6739;
    Display_ConfigureControl();
    func_02082ee0(7);
}

ARM void Scene_ResetPaletteB(void) {
    if (data_0212c5ac.blendEnabled != 0) {
        return;
    }
    func_0202a60c();
    *(u16 *)0x05000000 = 0x6739;
    *(u16 *)&data_021355a0 = 0x6739;
    func_0204bbb8();
    func_0204bb9c();
    Display_ConfigureControl();
}

ARM void Scene_LoadBackground(s32 index) {
    data_0212c75c.unk_c = 0;
    Scene_FlushDirtyTiles();
    *(u8 **)((u8 *)&data_02104a20 + 0xe8) = (u8 *)func_0208da4c() + 0x1bc;
    *(u8 **)((u8 *)&data_02104a20 + 0xb8) = data_02170504;
    *(u8 **)((u8 *)&data_02104a20 + 0xb4) = data_021361a0 + data_0212c618[3] * 0x800;
    OSi_CpuClear32(0, data_021361a0, 0x800);
    OSi_CpuClear32(0, data_021369a0, 0x800);
    func_0204c4bc((u16)index, data_02104ad4);
    func_0204c3a4(data_0216fcfc, data_0216fcfd, data_0216fcfe, data_0216fcff, (u16)index, data_02104ad4);
    func_020845b0(0x6014800, data_02170504, 0x1780);
    func_02026774();
}

ARM void Scene_FlushDirtyTiles(void) {
    u8 *tileMap = data_021361a0 + data_0212c618[3] * 0x800;
    s32 height = ((s8 *)&data_0216fcf8)[7];
    u32 row;
    u32 col;
    for (row = 0; row < height; row++) {
        for (col = 0; col < ((s8 *)&data_0216fcf8)[6]; col++) {
            *(u16 *)(tileMap + ((((s8 *)&data_0216fcf8)[4] + col) + ((((s8 *)&data_0216fcf8)[5] + row) << 5)) * 2) = 0;
        }
    }
    if (height != 0 || ((s8 *)&data_0216fcf8)[6] != 0) {
        OSi_CpuClear32(0, data_02170504, 0x1780);
        func_020845b0(0x6014800, data_02170504, 0x1780);
        func_02026774();
    }
    ((s8 *)&data_0216fcf8)[7] = 0;
    ((s8 *)&data_0216fcf8)[6] = 0;
    data_0212c75c.unk_c = 0;
}
