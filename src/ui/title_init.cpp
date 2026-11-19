#include "engine/functions.h"
#include "game/scene.h"
#include "engine/effect_state.h"
#include "engine/blend_request.h"
#include "engine/display_state.h"
#include "engine/map_state.h"
#include "engine/cockpit_state.h"
#include "engine/em2f_map_flag.h"
#include "engine/vblank_request.h"
#include "engine/disp_reset.h"

// title_init() (0x020527f0): sets up the title screen once the previous fade has finished: clears the display shadow,
// OAM and VRAM areas, loads the title graphics and colors, configures the BG layers and starts the effect state.
void title_init(void) {
    volatile u32 *dispcnt = (volatile u32 *)0x04000000;
    u8 zero = 0;
    u32 loadSlot;

    if (blendRequest.blendEnabled != 0) {
        return;
    }
    GX_DispOff();
    *dispcnt = ConvertDispCntToTWL(zero, *dispcnt);
    displayState.displayFlags = 0x40;
    MIi_CpuClearFast(0xc0, (void *)0x07000000, 0x400);
    MIi_CpuClearFast(0xc0, objAffineSet, 0x800);
    MIi_CpuClearFast(zero, data_0212ccb0, 0x200);
    data_0212c4e0 = zero;
    data_0212c4c8 = zero;
    data_0212c56c = (u32)data_0212ccb0;
    data_0212c570 = (u32)data_0212cdb0;
    data_0212c528 = (u32)objAffineSet;
    MessageInitialize();
    ObjWorkPoolClear();
    ObjMoveInit();
    MIi_CpuClearFast(zero, (void *)0x0601c000, 0x200);
    MIi_CpuClearFast(zero, (void *)0x06000800, 0x800);
    CgLoad(5);
    loadSlot = 3;
    DataLoad(loadSlot);
    em2f_mapFlag = zero;
    SetCgColor(zero, 0x6739);
    displayState.blendCnt = 0x3c64;
    displayState.bg[0].scrollY = zero;
    displayState.bg[0].cnt = 0x114;
    displayState.bg[0].buffer = data_021361a0;
    displayState.bg[1].scrollX = 0xfff8;
    displayState.bg[1].scrollY = 0xfff0;
    displayState.bg[1].cnt = 0x220 - loadSlot;
    displayState.bg[2].scrollX = zero;
    displayState.bg[2].scrollY = 0x5b;
    displayState.bg[3].scrollX = zero;
    displayState.bg[3].scrollY = 0x5b;
    mapState.scrollX = zero;
    mapState.scrollY = 0x5b;
    SetTblSetWorks(data_020d80d8);
    *(u32 *)&titleDialogBlock = *dispcnt & 0x300010;
    *dispcnt = (*dispcnt & 0xffcfffef) | 0x100010;
    effectState.messageIndex = zero;
    data_0212c4dc++;
    effectState.timer = 4;
}
