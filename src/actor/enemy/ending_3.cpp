#include "engine/functions.h"
#include "actor/enemy/ending.h"
#include "global.h"

// Implementer B, round 6: ending_scene_01 (0x02044b44).

void ending_scene_01(void) {
    u8 phase = effectState.phase;
    u8 i;
    switch (phase) {
    case 0:
        effectState.phase = phase + 1;
        effectState.timer = 0x3c;
        blendRequest.resetValue = 0x8877ffff;
        PaletteFade_ClearBufferFlag();
        blendRequest.blendColor = 0x1c;
        effectState.fadeStep = 0;
        SoundReq(0x1fe);
        break;
    case 1:
        if (effectState.fadeStep < 0x10) {
            if ((effectState.frames & 7) == 0) {
                effectState.fadeStep = effectState.fadeStep + 1;
            }
        } else {
            effectState.phase = phase + 1;
            effectState.timer = 0x3c;
        }
        MakeFadeBuff256(effectState.fadeStep << 4);
        title_MakeFadeBuff256(blendRequest.blendColor, effectState.fadeStep << 4);
        break;
    case 2:
        effectState.timer--;
        if (effectState.timer == 0) {
            for (i = 0; i < GAME_STATE_U8(0); i++) {
                playerWork[i].state = 0xc;
            }
            SoundReq(0x205);
            effectState.phase++;
        }
        break;
    case 3:
        if ((em12_typeMasks & 8) == 0) {
            break;
        }
        SoundReq(0x1ff);
        effectState.phase++;
        break;
    case 4:
        if (effectState.fadeStep != 0) {
            if ((effectState.frames & 7) == 0) {
                effectState.fadeStep = effectState.fadeStep - 1;
            }
        } else {
            blendRequest.resetValue = -1;
            PaletteFade_ClearBufferFlag();
            effectState.phase++;
            effectState.timer = 0x3c;
        }
        MakeFadeBuff256(effectState.fadeStep << 4);
        title_MakeFadeBuff256(blendRequest.blendColor, effectState.fadeStep << 4);
        break;
    case 5:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        effectState.phase = phase + 1;
        effectState.timer = 0x3c;
        playerWork[0].entity->animationState = 0;
        break;
    case 6:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        effectState.phase = phase + 1;
        MessageRequest(0x1fc);
        messageRequest.unk_03 = (messageRequest.unk_03 & ~0x1f) | 1;
        messageRequest.unk_04 = messageRequest.unk_04 & ~0x1f;
        break;
    case 7:
        if ((messageRequest.unk_00 & 0x7f) != 6) {
            break;
        }
        Status_ArmIfEnabled();
        effectState.phase++;
        break;
    case 8:
        if (ending_msgFinishWait() != 0) {
            break;
        }
        effectState.timer = 0xb4;
        effectState.phase++;
        SoundReq(0x800b0190);
        break;
    case 9:
        if (effectState.timer == 0x5a) {
            playerWork[0].entity->animationState = 2;
        } else if (effectState.timer == 0x52) {
            playerWork[0].entity->animationState = 4;
        }
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        effectState.phase++;
        effectState.timer = 0x46;
        blendRequest.resetValue = effectState.timer - 0x47;
        PaletteFade_ClearBufferFlag();
        FadeSet(1, 4);
        break;
    case 10:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        DispReset();
        *(u16 *)0x05000000 = 0;
        data_021355a0 = 0;
        ObjWorkPoolClear();
        ObjMoveInit();
        effectState.phase = 0;
        data_0212c4dc++;
        break;
    }
}

// ending_scene_02 (0x02044edc): sets up the display, then fades out and hands over to the task chain.
void ending_scene_02(void) {
    u32 dispcnt;
    switch (effectState.phase) {
    case 0:
        dispcnt = *(u32 *)0x04000000;
        *(u32 *)0x04000000 = (dispcnt & 0xffcfffef) | 0x10 | 0x100000;
        CgLoad(0xd);
        DataLoad(6);
        GetSetWork(0x28, 0, 0);
        GetSetWork(0x28, 3, 0);
        displayState.displayFlags |= 0x1000;
        effectState.phase++;
        effectState.timer = 0xf0;
        FadeSet(0, 4);
        break;
    case 1:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        effectState.timer = 0x3c;
        effectState.phase = effectState.phase + 1;
        FadeSet(1, 4);
        break;
    case 2:
        effectState.timer--;
        if (effectState.timer != 0) {
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
void bikkuri(void) {
    Entity *e = GetSetWork(0x5a, 1, 0x32);
    e->timer = 1;
    e->x.HALF.HI = 0x1f8;
    e->y.HALF.HI = 0x1a0;
}

// ending_finale (0x02045060): runs the phase handler, then recolours a palette row once the flags allow it.
void ending_finale(void) {
    u8 *palette;
    endingFinaleTable[data_0212c4dc]();
    if (em12_typeMasks & 0x10) {
        return;
    }
    if ((data_0212c594 & 3) != 0) {
        return;
    }
    if (blendRequest.blendEnabled != 0) {
        return;
    }
    palette = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x3a);
    CgPalletSet((u16 *)(palette + ((Random() & 3) << 5)), 0xf, 1);
}
