#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/os_valarm.h"
#include "sdk/os/os_irq.h"
#include "sdk/os/os_irq_state.h"
#include "sdk/gx/gx.h"

void OSi_SetNextVAlarm(OsVAlarm *alarm) {
    OS_SetIrqFunction(4, OSi_VAlarmHandler);
    GX_SetVCountEqVal(alarm->vcount);
    *(volatile u16 *)0x04000004 |= 0x20;
    OS_EnableIrqMask(4);
}

void OSi_VAlarmHandler(void) {
    OsVAlarm *alarm;
    u32 frame;
    s32 currentLine;
    void (*handler)(void *);
    s32 state;

    OS_DisableIrqMask(4);
    *(volatile u16 *)0x04000004 &= 0xffdf;
    OS_IRQ_CHECK_FLAG |= 4;
    {
        u16 vcountReg = *(volatile u16 *)0x04000004;
        OSi_GetVFrame(((vcountReg >> 8) & 0xff | (vcountReg << 1) & 0x100) - 1);
    }
    alarm = data_02129c7c.head;
    while (alarm != NULL) {
        currentLine = *(volatile u16 *)0x04000006;
        frame = OSi_GetVFrame(currentLine);
        state = OSi_CompareVCount(alarm, frame, currentLine);
        switch (state) {
        case 0:
            OSi_SetNextVAlarm(alarm);
            currentLine = *(volatile u16 *)0x04000006;
            if (alarm->vcount != currentLine || alarm->frame != frame) {
                return;
            }
            OS_DisableIrqMask(4);
            *(volatile u16 *)0x04000004 &= 0xffdf;
            OS_ResetRequestIrqMask(4);
        case 1:
            handler = alarm->handler;
            OSi_DetachVAlarm(alarm);
            alarm->handler = NULL;
            if (handler != NULL) {
                handler(alarm->argument);
            }
            if (alarm->period == 0 || alarm->canceled != 0) {
                break;
            }
            alarm->handler = handler;
            goto reinsert;
        case 2:
            OSi_DetachVAlarm(alarm);
        reinsert:
            alarm->frame = data_02129c7c.frame + 1;
            OSi_InsertVAlarm(alarm);
            break;
        }
        alarm = data_02129c7c.head;
    }
}

s32 OSi_CompareVCount(OsVAlarm *alarm, s32 frame, s32 vcount) {
    s32 frameDiff;
    s32 lineDiff;

    frameDiff = frame - alarm->frame;
    lineDiff = vcount - alarm->vcount;
    if (frameDiff < 0 || (frameDiff == 0 && lineDiff < 0)) {
        return 0;
    }
    if (lineDiff < 0) {
        lineDiff += 0x107;
    }
    if (lineDiff <= alarm->delay) {
        return 1;
    }
    return 2;
}

s32 OSi_GetVFrame(s32 vcount) {
    u32 irq;

    irq = OS_DisableInterrupts();
    if (vcount < data_02129c7c.lastVCount) {
        data_02129c7c.frame++;
    }
    data_02129c7c.lastVCount = vcount;
    OS_RestoreInterrupts(irq);
    return data_02129c7c.frame;
}
