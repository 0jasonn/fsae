#include "game/scene_d.h"
#include "global.h"

// pause_dialogDisp -> pause_dialogDisp (guess): clears the 0x800 byte buffer data_0216f020 and sets up the
// table at data_0211474c (the same block that Pause reads the handler table from).
ARM void pause_dialogDisp(s32 index, s32 unused, s32 value) {
    MI_CpuFill(data_0216f020, 0, 0x800);
    *(u16 *)((u8 *)&data_0211474c + 0x30) = 0x3090;
    *(u8 **)((u8 *)&data_0211474c + 0x20) = data_0216f020;
    *(u8 **)((u8 *)&data_0211474c + 0x54) = (u8 *)KnifeApp_getInstance() + 0x1bc;
    *((u8 *)&data_0211474c + 0x32) = 0x17;
    *(u32 *)((u8 *)&data_0211474c + 0x2c) = 0;
    Knife_Message_selectionDialog_initWithMsgScrn(data_02171c84, data_0211476c);
    Knife_Message_selectionDialog_setVisible(data_02171c84, 1);
    Knife_Message_selectionDialog_doModal(data_02171c84, (u16)index, 0, value, 0);
}
