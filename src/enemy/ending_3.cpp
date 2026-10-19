#include "engine/functions.h"
#include "enemy/ending.h"
#include "global.h"

// Implementer B, round 6: ending_scene_01 (0x02044b44).

ARM void ending_scene_01(void) {
    u8 phase = data_021349c0.phase;
    u8 i;
    switch (phase) {
    case 0:
        data_021349c0.phase = phase + 1;
        data_021349c0.timer = 0x3c;
        data_0212c5ac.resetValue = 0x8877ffff;
        PaletteFade_ClearBufferFlag();
        data_0212c5ac.blendColor = 0x1c;
        data_021349c0.fadeStep = 0;
        SoundReq(0x1fe);
        break;
    case 1:
        if (data_021349c0.fadeStep < 0x10) {
            if ((data_021349c0.frames & 7) == 0) {
                data_021349c0.fadeStep = data_021349c0.fadeStep + 1;
            }
        } else {
            data_021349c0.phase = phase + 1;
            data_021349c0.timer = 0x3c;
        }
        MakeFadeBuff256(data_021349c0.fadeStep << 4);
        title_MakeFadeBuff256(data_0212c5ac.blendColor, data_021349c0.fadeStep << 4);
        break;
    case 2:
        data_021349c0.timer--;
        if (data_021349c0.timer == 0) {
            for (i = 0; i < GAME_STATE_U8(0); i++) {
                data_0212ceb0[i].state = 0xc;
            }
            SoundReq(0x205);
            data_021349c0.phase++;
        }
        break;
    case 3:
        if ((em12_typeMasks & 8) == 0) {
            break;
        }
        SoundReq(0x1ff);
        data_021349c0.phase++;
        break;
    case 4:
        if (data_021349c0.fadeStep != 0) {
            if ((data_021349c0.frames & 7) == 0) {
                data_021349c0.fadeStep = data_021349c0.fadeStep - 1;
            }
        } else {
            data_0212c5ac.resetValue = -1;
            PaletteFade_ClearBufferFlag();
            data_021349c0.phase++;
            data_021349c0.timer = 0x3c;
        }
        MakeFadeBuff256(data_021349c0.fadeStep << 4);
        title_MakeFadeBuff256(data_0212c5ac.blendColor, data_021349c0.fadeStep << 4);
        break;
    case 5:
        data_021349c0.timer--;
        if (data_021349c0.timer != 0) {
            break;
        }
        data_021349c0.phase = phase + 1;
        data_021349c0.timer = 0x3c;
        data_0212ceb0[0].entity->animationState = 0;
        break;
    case 6:
        data_021349c0.timer--;
        if (data_021349c0.timer != 0) {
            break;
        }
        data_021349c0.phase = phase + 1;
        MessageRequest(0x1fc);
        messageRequest.unk_03 = (messageRequest.unk_03 & ~0x1f) | 1;
        messageRequest.unk_04 = messageRequest.unk_04 & ~0x1f;
        break;
    case 7:
        if ((messageRequest.unk_00 & 0x7f) != 6) {
            break;
        }
        Status_ArmIfEnabled();
        data_021349c0.phase++;
        break;
    case 8:
        if (ending_msgFinishWait() != 0) {
            break;
        }
        data_021349c0.timer = 0xb4;
        data_021349c0.phase++;
        SoundReq(0x800b0190);
        break;
    case 9:
        if (data_021349c0.timer == 0x5a) {
            data_0212ceb0[0].entity->animationState = 2;
        } else if (data_021349c0.timer == 0x52) {
            data_0212ceb0[0].entity->animationState = 4;
        }
        data_021349c0.timer--;
        if (data_021349c0.timer != 0) {
            break;
        }
        data_021349c0.phase++;
        data_021349c0.timer = 0x46;
        data_0212c5ac.resetValue = data_021349c0.timer - 0x47;
        PaletteFade_ClearBufferFlag();
        FadeSet(1, 4);
        break;
    case 10:
        data_021349c0.timer--;
        if (data_021349c0.timer != 0) {
            break;
        }
        DispReset();
        *(u16 *)0x05000000 = 0;
        data_021355a0 = 0;
        ObjWorkPoolClear();
        ObjMoveInit();
        data_021349c0.phase = 0;
        data_0212c4dc++;
        break;
    }
}

// ending_scene_02 (0x02044edc): sets up the display, then fades out and hands over to the task chain.
ARM void ending_scene_02(void) {
    u32 dispcnt;
    switch (data_021349c0.phase) {
    case 0:
        dispcnt = *(u32 *)0x04000000;
        *(u32 *)0x04000000 = (dispcnt & 0xffcfffef) | 0x10 | 0x100000;
        CgLoad(0xd);
        DataLoad(6);
        GetSetWork(0x28, 0, 0);
        GetSetWork(0x28, 3, 0);
        data_0212c75c.displayFlags |= 0x1000;
        data_021349c0.phase++;
        data_021349c0.timer = 0xf0;
        FadeSet(0, 4);
        break;
    case 1:
        data_021349c0.timer--;
        if (data_021349c0.timer != 0) {
            break;
        }
        data_021349c0.timer = 0x3c;
        data_021349c0.phase = data_021349c0.phase + 1;
        FadeSet(1, 4);
        break;
    case 2:
        data_021349c0.timer--;
        if (data_021349c0.timer != 0) {
            break;
        }
        DispReset();
        *(u16 *)0x05000000 = 0;
        data_021355a0 = 0;
        ObjWorkPoolClear();
        ObjMoveInit();
        dispcnt = *(u32 *)0x04000000;
        *(u32 *)0x04000000 = (dispcnt & 0xffcfffef) | 0x10;
        Task_Chain(0xa);
        break;
    }
}

// bikkuri (0x02045030): spawns the flag actor at the top right and sets its timer.
ARM void bikkuri(void) {
    Entity *e = GetSetWork(0x5a, 1, 0x32);
    e->timer = 1;
    e->x.HALF.HI = 0x1f8;
    e->y.HALF.HI = 0x1a0;
}

// ending_finale (0x02045060): runs the phase handler, then recolours a palette row once the flags allow it.
ARM void ending_finale(void) {
    u8 *palette;
    endingFinaleTable[data_0212c4dc]();
    if (em12_typeMasks & 0x10) {
        return;
    }
    if ((data_0212c594 & 3) != 0) {
        return;
    }
    if (data_0212c5ac.blendEnabled != 0) {
        return;
    }
    palette = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x3a);
    CgPalletSet((u16 *)(palette + ((Random() & 3) << 5)), 0xf, 1);
}
