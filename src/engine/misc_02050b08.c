#include "engine/misc_d.h"
#include "global.h"

ARM void GameMode_Step(void) {
    Random();
    data_02104a24[data_0212c500]();
    Effect_StepTimer();
}

ARM s32 EntityList_HasTaggedType5(void) {
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
ARM void EntityList_ProcessTaggedEntities(void) {
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
        EntityNode *h2;
        EntityNode *m;
        EntityNode *p;
        for (h2 = data_0212c6b0; h2 < data_0212c6f0; h2++) {
            m = h2->next;
            if (m != h2) {
                do {
                    if (((Entity *)m)->unk_08 == 6 && ((Entity *)m)->unk_09 == 0x28 && ((Entity *)m)->type == 5) {
                        p = m->prev;
                        DeleteEntity((Entity *)m);
                        m = p;
                    }
                    m = m->next;
                } while (m != h2);
            }
        }
    }
}

ARM void GameMode_Init(void) {
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
    func_0202a60c();
    func_0205b700();
    ((u8 *)&data_0212c7c8)[0x8e] = 0;
    Global_AllocBlock();
    PaletteFade_Init();
    func_0204bbb8();
    func_0204bb9c();
    func_02080e58();
    func_02027dc4();
    func_0202a92c();
    State_ClearWorkBuffers();
    func_0204f978();
    MIi_CpuClear16(0, data_021349c0, 0x28);
    func_02054b64();
    func_02054c04();
    slotIndex = 0x17;
    func_02029b38(slotIndex);
    setupIndexA = 1;
    func_02029fe8(setupIndexA);
    setupIndexB = 2;
    func_02029fe8(setupIndexB);
    func_02027ec4(0x12);
    {
        s32 valueA = setupIndexA + 0x218;
        s32 valueB = slotIndex + 0x670;
        bankValue -= 0x80000010;
        data_02134924 = zero;
        data_0212c504 = zero;
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
        data_02134914 = zero;
    }
    data_0212c75c.displayFlags |= 0x1b00;
    func_02026774();
    ((u8 *)func_0208da4c())[0xcb0] = 0;
    *(volatile u32 *)0x04000000 = (*(volatile u32 *)0x04000000 & 0xffcfffef) | 0x10;
    data_021349c0[EFFECT_STATE_STEP_TIMER] = 0xb4;
    data_021349c0[EFFECT_STATE_STEP_INDEX] = zero;
    data_021349c0[EFFECT_STATE_ACTIVE] = zero;
    data_021349c0[EFFECT_STATE_LEVEL] = zero;
    data_0212c5ac.resetValue = -1;
    PaletteFade_ClearBufferFlag();
    func_0204625c(setupIndexB, 4);
    data_0212c5ac.blendColor = 0x19;
    func_020463f0(0x100);
    Palette_BlendTowardColor(data_0212c5ac.blendColor, 0x100);
    {
        Entity *spawned = CreateFx(0x5a, setupIndexB, zero);
        spawned->x.HALF.HI = 0x80;
        spawned->y.HALF.HI = 0xf0;
    }
    data_0212c500++;
    if (data_0212c4dc != 0) {
        Effect_Start();
    } else {
        GX_DispOn();
    }
    *(volatile u32 *)0x04001000 |= 0x10000;
}

// Steps the effect timer and scans data_02104a58 for the next value to write (guess: a 16-bit value table).
ARM void Effect_StepTimer(void) {
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
    stepValue = data_02104a58[stepIndex];
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

ARM void Effect_Update(void) {
    u8 *base;
    if (data_021349c0[EFFECT_STATE_ACTIVE] == 0) {
        return;
    }
    if (data_0212c5ac.blendEnabled != 0) {
        return;
    }
    if ((data_0212c594 & 3) == 0) {
        base = func_0208ddcc(func_0208da4c(), 0x3a);
        func_02029c60((s32)(base + ((Random() & 3) << 5)), 0xf, 1);
    }
    func_020463f0(data_021349c0[EFFECT_STATE_LEVEL] << 4);
    Palette_BlendTowardColor(data_0212c5ac.blendColor, data_021349c0[EFFECT_STATE_LEVEL] << 4);
}

ARM void Effect_Start(void) {
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
    func_02029d0c(0, 0x6739);
    func_0204625c(3, 0x20);
}

ARM s32 GameMode_IsRunning(void) {
    return data_0212c500 == 2;
}

ARM void GameMode_Update(void) {
    data_02104a40[data_0212c4dc]();
    data_0212c564();
    func_020830ec();
    func_02080ed4();
    Effect_Update();
}
