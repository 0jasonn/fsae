#include "engine/functions.h"
#include "game/scene_d.h"
#include "global.h"

// title_timeout -> title_timeout
// title_back -> title_back
// knife_title_dialogDisp -> knife_title_dialogDisp
// knife_title_dialogDelete -> knife_title_dialogDelete
// Region of the tile map to flush is paletteFade bytes [4..7]: x, y, width, height (tiles).
ARM void title_timeout(void) {
    if (data_0212c5ac.blendEnabled != 0) {
        return;
    }
    DispReset();
    *(u16 *)0x05000000 = 0x6739;
    *(u16 *)&data_021355a0 = 0x6739;
    OpeningTaskFinalzie();
    Task_Chain(7);
}

ARM void title_back(void) {
    if (data_0212c5ac.blendEnabled != 0) {
        return;
    }
    DispReset();
    *(u16 *)0x05000000 = 0x6739;
    *(u16 *)&data_021355a0 = 0x6739;
    ObjMoveInit();
    ObjWorkPoolClear();
    OpeningTaskFinalzie();
}

ARM void knife_title_dialogDisp(s32 index) {
    data_0212c75c.unk_c = 0;
    knife_title_dialogDelete();
    *(u8 **)((u8 *)&titleDialogBlock + 0xe8) = (u8 *)KnifeApp_getInstance() + 0x1bc;
    *(u8 **)((u8 *)&titleDialogBlock + 0xb8) = titleDialogBuffer;
    *(u8 **)((u8 *)&titleDialogBlock + 0xb4) = data_021361a0 + data_0212c618[3] * 0x800;
    OSi_CpuClear32(0, data_021361a0, 0x800);
    OSi_CpuClear32(0, data_021369a0, 0x800);
    knife_MakeMsgScreen((u16)index, titleDialogData);
    getDialogXYZWH(data_0216fcfc, data_0216fcfd, data_0216fcfe, data_0216fcff, (u16)index, titleDialogData);
    func_020845b0(0x6014800, titleDialogBuffer, 0x1780);
    func_02026774();
}

ARM void knife_title_dialogDelete(void) {
    u8 *tileMap = data_021361a0 + data_0212c618[3] * 0x800;
    s32 height = ((s8 *)&paletteFade)[7];
    u32 row;
    u32 col;
    for (row = 0; row < height; row++) {
        for (col = 0; col < ((s8 *)&paletteFade)[6]; col++) {
            *(u16 *)(tileMap + ((((s8 *)&paletteFade)[4] + col) + ((((s8 *)&paletteFade)[5] + row) << 5)) * 2) = 0;
        }
    }
    if (height != 0 || ((s8 *)&paletteFade)[6] != 0) {
        OSi_CpuClear32(0, titleDialogBuffer, 0x1780);
        func_020845b0(0x6014800, titleDialogBuffer, 0x1780);
        func_02026774();
    }
    ((s8 *)&paletteFade)[7] = 0;
    ((s8 *)&paletteFade)[6] = 0;
    data_0212c75c.unk_c = 0;
}
