#include "engine/functions.h"
#include "game/scene_d.h"
#include "global.h"

// pause_dialogDisp -> pause_dialogDisp (guess): clears the 0x800 byte buffer pauseDialogBuffer and sets up the
// table at pauseHandlerTable (the same block that Pause reads the handler table from).
ARM void pause_dialogDisp(s32 index, s32 unused, s32 value) {
    MI_CpuFill(pauseDialogBuffer, 0, 0x800);
    *(u16 *)((u8 *)&pauseHandlerTable + 0x30) = 0x3090;
    *(u8 **)((u8 *)&pauseHandlerTable + 0x20) = pauseDialogBuffer;
    *(u8 **)((u8 *)&pauseHandlerTable + 0x54) = (u8 *)KnifeApp_getInstance() + 0x1bc;
    *((u8 *)&pauseHandlerTable + 0x32) = 0x17;
    *(u32 *)((u8 *)&pauseHandlerTable + 0x2c) = 0;
    Knife_Message_selectionDialog_initWithMsgScrn(pauseDialogWindow, pauseDialogRect);
    Knife_Message_selectionDialog_setVisible(pauseDialogWindow, 1);
    Knife_Message_selectionDialog_doModal(pauseDialogWindow, (u16)index, 0, value, 0);
}
