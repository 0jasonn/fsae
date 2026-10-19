#include "engine/functions.h"
#include "engine/misc_d.h"
#include "global.h"

ARM void OpeningTask(void) {
    Random();
    data_02104a24[data_0212c500]();
    mist_effect();
}

ARM s32 OpeningTaskCanPrepareFinalize(void) {
    EntityNode *head;
    EntityNode *node;
    for (head = data_0212c6b0; head < data_0212c6f0; head++) {
        node = head->next;
        if (node != head) {
            do {
                if (((Entity *)node)->unk_08 == 6 && ((Entity *)node)->unk_09 == 0x28 && ((Entity *)node)->type == 5) {
                    return 0;
                }
                node = node->next;
            } while (node != head);
        }
    }
    return 1;
}

// Marks type-0 tagged entities as subtimer 1, then deletes the type-5 tagged ones.
ARM void OpeningTaskPrepareFinalize(void) {
    EntityNode *head;
    EntityNode *node;
    for (head = data_0212c6b0; head < data_0212c6f0; head++) {
        node = head->next;
        if (node != head) {
            do {
                if (((Entity *)node)->unk_08 == 6 && ((Entity *)node)->unk_09 == 0x28 && ((Entity *)node)->type == 0) {
                    ((Entity *)node)->subtimer = 1;
                    break;
                }
                node = node->next;
            } while (node != head);
        }
    }
    {
        EntityNode *head2;
        EntityNode *node2;
        EntityNode *prevNode;
        for (head2 = data_0212c6b0; head2 < data_0212c6f0; head2++) {
            node2 = head2->next;
            if (node2 != head2) {
                do {
                    if (((Entity *)node2)->unk_08 == 6 && ((Entity *)node2)->unk_09 == 0x28 && ((Entity *)node2)->type == 5) {
                        prevNode = node2->prev;
                        PutObjWork((Entity *)node2);
                        node2 = prevNode;
                    }
                    node2 = node2->next;
                } while (node2 != head2);
            }
        }
    }
}

ARM void op_init(void) {
    u32 bankValue = 0x80010000;
    s32 slotIndex;
    s32 setupIndexA;
    s32 setupIndexB;
    s32 zero = 0;
    if (data_0212c5ac.blendEnabled != 0) {
        return;
    }
    if (data_0212c4bc != 0) {
        GX_DispOff();
    }
    data_0212c4f8 = 0;
    SoundReq(bankValue);
    SoundReq(0x800b01ad);
    DispReset();
    ZeldaFadeFinish();
    ((u8 *)&data_0212c7c8)[0x8e] = 0;
    initializeVirtualScreenData();
    setupVirtualScreenCallback();
    ObjMoveInit();
    func_0204bb9c();
    VGroupInit();
    InitObjColor();
    DemoBgBuffClear();
    MessageInitialize();
    func_0204f978();
    MIi_CpuClear16(0, data_021349c0, 0x28);
    PlWorkClear();
    PlWorkColorReset();
    slotIndex = 0x17;
    CgLoad(slotIndex);
    setupIndexA = 1;
    DataLoad(setupIndexA);
    setupIndexB = 2;
    DataLoad(setupIndexB);
    GetObjColor(0x12);
    {
        s32 valueA = setupIndexA + 0x218;
        s32 valueB = slotIndex + 0x670;
        bankValue -= 0x80000010;
        data_02134924 = zero;
        localPlayerIndex = zero;
        data_0212c618[0] = zero;
        data_0212c618[3] = zero;
        data_0212c75c.workBuffer = data_021361a0;
        data_0212c75c.unk_8 = *(const u16 *)(data_020ce4d0 + 0x24);
        data_0212c75c.unk_14 = valueA;
        data_0212c75c.unk_20 = 0x841a;
        data_0212c75c.unk_2c = valueB;
        data_0212c75c.reg66 = 0x3e66;
        data_0212c75c.reg68 = 0x0c0c;
        data_0212c75c.unk_a = zero;
        data_0212c75c.unk_c = bankValue;
        data_0212c75c.frameCounter = zero;
        data_0212c75c.unk_18 = bankValue;
        data_0212c75c.unk_22 = zero;
        data_0212c75c.scrollX = zero;
        data_0212c75c.unk_2e = zero;
        data_0212c75c.unk_30 = 0xb0;
        data_0212c648.unk_20 = zero;
        data_0212c648.cameraX = 0xb0;
        em2f_mapFlag = zero;
    }
    data_0212c75c.displayFlags |= 0x1b00;
    func_02026774();
    ((u8 *)KnifeApp_getInstance())[0xcb0] = 0;
    *(volatile u32 *)0x04000000 = (*(volatile u32 *)0x04000000 & 0xffcfffef) | 0x10;
    data_021349c0[EFFECT_STATE_STEP_TIMER] = 0xb4;
    data_021349c0[EFFECT_STATE_STEP_INDEX] = zero;
    data_021349c0[EFFECT_STATE_ACTIVE] = zero;
    data_021349c0[EFFECT_STATE_LEVEL] = zero;
    data_0212c5ac.resetValue = -1;
    PaletteFade_ClearBufferFlag();
    FadeSet(setupIndexB, 4);
    data_0212c5ac.blendColor = 0x19;
    MakeFadeBuff256(0x100);
    title_MakeFadeBuff256(data_0212c5ac.blendColor, 0x100);
    {
        Entity *spawned = GetSetWork(0x5a, setupIndexB, zero);
        spawned->x.HALF.HI = 0x80;
        spawned->y.HALF.HI = 0xf0;
    }
    data_0212c500++;
    if (data_0212c4dc != 0) {
        op_demo_skip();
    } else {
        GX_DispOn();
    }
    *(volatile u32 *)0x04001000 |= 0x10000;
}

// Steps the effect timer and scans mistStepTable for the next value to write (guess: a 16-bit value table).
ARM void mist_effect(void) {
    u8 stepIndex;
    u16 stepValue;
    if (data_021349c0[EFFECT_STATE_ACTIVE] != 0) {
        return;
    }
    if ((data_0212c594 & 3) == 0) {
        data_0212c75c.frameCounter++;
    }
    if (data_021349c0[EFFECT_STATE_STEP_TIMER] != 0) {
        data_021349c0[EFFECT_STATE_STEP_TIMER]--;
        return;
    }
    if ((data_0212c594 & 7) != 0) {
        return;
    }
    stepIndex = data_021349c0[EFFECT_STATE_STEP_INDEX];
    stepValue = mistStepTable[stepIndex];
    if (stepValue != 0xffff && stepIndex != 0xff) {
        data_021349c0[EFFECT_STATE_STEP_INDEX] = stepIndex + 1;
        data_0212c75c.reg68 = stepValue;
        return;
    }
    data_0212c75c.displayFlags &= 0xfdff;
    data_0212c75c.displayFlags |= 0x400;
    data_0212c75c.reg66 = 0x3c64;
    data_0212c75c.reg68 = 0x808;
    data_0212c75c.scrollX = data_0212c648.cameraX;
    data_021349c0[EFFECT_STATE_ACTIVE] = 1;
}

ARM void color_control(void) {
    u8 *base;
    if (data_021349c0[EFFECT_STATE_ACTIVE] == 0) {
        return;
    }
    if (data_0212c5ac.blendEnabled != 0) {
        return;
    }
    if ((data_0212c594 & 3) == 0) {
        base = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x3a);
        CgPalletSet((u16 *)(base + ((Random() & 3) << 5)), 0xf, 1);
    }
    MakeFadeBuff256(data_021349c0[EFFECT_STATE_LEVEL] << 4);
    title_MakeFadeBuff256(data_0212c5ac.blendColor, data_021349c0[EFFECT_STATE_LEVEL] << 4);
}

ARM void op_demo_skip(void) {
    if (data_0212c500 != 1) {
        return;
    }
    SoundReq(0x80010000);
    data_0212c5ac.resetValue = -1;
    PaletteFade_ClearBufferFlag();
    data_021349c0[EFFECT_STATE_STEP_TIMER] = 0;
    data_021349c0[EFFECT_STATE_STEP_INDEX] = 0xff;
    data_0212c500 = 2;
    data_0212c4dc = 0;
    SetCgColor(0, 0x6739);
    FadeSet(3, 0x20);
}

ARM s32 is_op_demo_end(void) {
    return data_0212c500 == 2;
}

ARM void op_demo(void) {
    data_02104a40[data_0212c4dc]();
    data_0212c564();
    func_020830ec();
    VGroupManager();
    color_control();
}
