#include "engine/functions.h"
#include "engine/misc.h"
#include "global.h"

void OpeningTask(void) {
    Random();
    data_02104a24[data_0212c500]();
    mist_effect();
}

s32 OpeningTaskCanPrepareFinalize(void) {
    EntityNode *head;
    EntityNode *node;
    for (head = data_0212c6b0; head < data_0212c6f0; head++) {
        node = head->next;
        if (node != head) {
            do {
                if (((Entity *)node)->objKind == 6 && ((Entity *)node)->objId == 0x28 && ((Entity *)node)->type == 5) {
                    return 0;
                }
                node = node->next;
            } while (node != head);
        }
    }
    return 1;
}

// Marks type-0 tagged entities as subtimer 1, then deletes the type-5 tagged ones.
void OpeningTaskPrepareFinalize(void) {
    EntityNode *head;
    EntityNode *node;
    for (head = data_0212c6b0; head < data_0212c6f0; head++) {
        node = head->next;
        if (node != head) {
            do {
                if (((Entity *)node)->objKind == 6 && ((Entity *)node)->objId == 0x28 && ((Entity *)node)->type == 0) {
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
                    if (((Entity *)node2)->objKind == 6 && ((Entity *)node2)->objId == 0x28 && ((Entity *)node2)->type == 5) {
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

void op_init(void) {
    u32 bankValue = 0x80010000;
    s32 slotIndex;
    s32 setupIndexA;
    s32 setupIndexB;
    s32 zero = 0;
    if (blendRequest.blendEnabled != 0) {
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
    ((u8 *)&gameState)[0x8e] = 0;
    initializeVirtualScreenData();
    setupVirtualScreenCallback();
    ObjMoveInit();
    ObjWorkPoolClear();
    VGroupInit();
    InitObjColor();
    DemoBgBuffClear();
    MessageInitialize();
    func_0204f978();
    MIi_CpuClear16(0, effectState, 0x28);
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
        cockpitState[0] = zero;
        cockpitState[3] = zero;
        displayState.workBuffer = data_021361a0;
        displayState.unk_8 = *(const u16 *)(data_020ce4d0 + 0x24);
        displayState.unk_14 = valueA;
        displayState.unk_20 = 0x841a;
        displayState.unk_2c = valueB;
        displayState.reg66 = 0x3e66;
        displayState.reg68 = 0x0c0c;
        displayState.unk_a = zero;
        displayState.unk_c = bankValue;
        displayState.frameCounter = zero;
        displayState.unk_18 = bankValue;
        displayState.unk_22 = zero;
        displayState.scrollX = zero;
        displayState.unk_2e = zero;
        displayState.unk_30 = 0xb0;
        mapState.unk_20 = zero;
        mapState.cameraX = 0xb0;
        em2f_mapFlag = zero;
    }
    displayState.displayFlags |= 0x1b00;
    func_02026774();
    ((u8 *)KnifeApp_getInstance())[0xcb0] = 0;
    *(volatile u32 *)0x04000000 = (*(volatile u32 *)0x04000000 & 0xffcfffef) | 0x10;
    effectState[EFFECT_STATE_STEP_TIMER] = 0xb4;
    effectState[EFFECT_STATE_STEP_INDEX] = zero;
    effectState[EFFECT_STATE_ACTIVE] = zero;
    effectState[EFFECT_STATE_LEVEL] = zero;
    blendRequest.resetValue = -1;
    PaletteFade_ClearBufferFlag();
    FadeSet(setupIndexB, 4);
    blendRequest.blendColor = 0x19;
    MakeFadeBuff256(0x100);
    title_MakeFadeBuff256(blendRequest.blendColor, 0x100);
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
void mist_effect(void) {
    u8 stepIndex;
    u16 stepValue;
    if (effectState[EFFECT_STATE_ACTIVE] != 0) {
        return;
    }
    if ((data_0212c594 & 3) == 0) {
        displayState.frameCounter++;
    }
    if (effectState[EFFECT_STATE_STEP_TIMER] != 0) {
        effectState[EFFECT_STATE_STEP_TIMER]--;
        return;
    }
    if ((data_0212c594 & 7) != 0) {
        return;
    }
    stepIndex = effectState[EFFECT_STATE_STEP_INDEX];
    stepValue = mistStepTable[stepIndex];
    if (stepValue != 0xffff && stepIndex != 0xff) {
        effectState[EFFECT_STATE_STEP_INDEX] = stepIndex + 1;
        displayState.reg68 = stepValue;
        return;
    }
    displayState.displayFlags &= 0xfdff;
    displayState.displayFlags |= 0x400;
    displayState.reg66 = 0x3c64;
    displayState.reg68 = 0x808;
    displayState.scrollX = mapState.cameraX;
    effectState[EFFECT_STATE_ACTIVE] = 1;
}

void color_control(void) {
    u8 *base;
    if (effectState[EFFECT_STATE_ACTIVE] == 0) {
        return;
    }
    if (blendRequest.blendEnabled != 0) {
        return;
    }
    if ((data_0212c594 & 3) == 0) {
        base = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x3a);
        CgPalletSet((u16 *)(base + ((Random() & 3) << 5)), 0xf, 1);
    }
    MakeFadeBuff256(effectState[EFFECT_STATE_LEVEL] << 4);
    title_MakeFadeBuff256(blendRequest.blendColor, effectState[EFFECT_STATE_LEVEL] << 4);
}

void op_demo_skip(void) {
    if (data_0212c500 != 1) {
        return;
    }
    SoundReq(0x80010000);
    blendRequest.resetValue = -1;
    PaletteFade_ClearBufferFlag();
    effectState[EFFECT_STATE_STEP_TIMER] = 0;
    effectState[EFFECT_STATE_STEP_INDEX] = 0xff;
    data_0212c500 = 2;
    data_0212c4dc = 0;
    SetCgColor(0, 0x6739);
    FadeSet(3, 0x20);
}

s32 is_op_demo_end(void) {
    return data_0212c500 == 2;
}

void op_demo(void) {
    data_02104a40[data_0212c4dc]();
    data_0212c564();
    func_020830ec();
    VGroupManager();
    color_control();
}
