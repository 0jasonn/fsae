#include "game/scene_d.h"
#include "global.h"

// Scene_InitObjects -> Scene_InitObjects (guess): clears the 0x800 byte buffer data_0216f020 and sets up the
// table at data_0211474c (the same block that Scene_CallStateHandler reads the handler table from).
ARM void Scene_InitObjects(s32 index, s32 unused, s32 value) {
    MI_CpuFill(data_0216f020, 0, 0x800);
    *(u16 *)((u8 *)&data_0211474c + 0x30) = 0x3090;
    *(u8 **)((u8 *)&data_0211474c + 0x20) = data_0216f020;
    *(u8 **)((u8 *)&data_0211474c + 0x54) = (u8 *)func_0208da4c() + 0x1bc;
    *((u8 *)&data_0211474c + 0x32) = 0x17;
    *(u32 *)((u8 *)&data_0211474c + 0x2c) = 0;
    func_020a1a30(data_02171c84, data_0211476c);
    func_020a2138(data_02171c84, 1);
    func_020a1a88(data_02171c84, (u16)index, 0, value, 0);
}
