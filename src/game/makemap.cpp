#include "engine/functions.h"
#include "game/multiplay.h"
#include "global.h"

// makemap_* (0x02047838 to 0x02047b14). makemap_sync_0204794c is a three-phase sync helper, makemap_nop_020479d4 is a bare return.

ARM void makemap_00(void) {
    u8 i;
    ObjWorkPoolClear();
    BgInit();
    ObjMoveInit();
    CheckInit();
    ShikakeInit();
    VGroupInit();
    InitObjColor();
    func_02029a50(data_0212caf0, 0x1c0);
    PlWorkReset();
    for (i = 0; i < 4; i++) {
        PLAYER_BYTE(i, 0x1c) = GS_U8(0x58 + i);
    }
    GS_U8(0x8e) = 0;
    CgLoad(2);
    DataLoad(0x10);
    *(u16 *)0x05000000 = 0;
    data_021355a0 = 0;
    data_0212c4dc++;
    data_0216efa8 = 0;
    *(u16 *)(data_0212c5bc + 2) = 0xa;
    SetCgColor(0, 0);
    SetCgColor(0xe, 0xffff);
    data_0212c75c.displayFlags = 0;
    *(u32 *)0x04000000 = ConvertDispCntToTWL(0, *(u32 *)0x04000000);
    Knife_Single_SinglePlay_GetInstance();
    Knife_Single_SinglePlay_Initialize();
}

// makemap_* (0x0204794c to 0x02047b14). makemap_sync_0204794c is a three-phase sync helper, makemap_nop_020479d4 is a bare return.

ARM void makemap_sync_0204794c(void) {
    switch (data_0216efa8) {
    case 0:
        ComRequest(4);
        data_0216efa8++;
        break;
    case 1:
        if (WXC_GetStateCode() == 1) {
            data_0216efa8++;
        }
        break;
    case 2: {
        u8 zero = 0;
        data_0212c4dc += 2;
        data_0216efa8 = zero;
        data_021349c0.unk_02[1] = zero;
        break;
    }
    }
}

ARM void makemap_nop_020479d4(void) {
}
