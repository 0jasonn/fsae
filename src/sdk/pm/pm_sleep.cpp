#include "global.h"
#include "types.h"
#include "sdk/os/os_boot.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/os/os_irq.h"
#include "sdk/os/os_halt_api.h"
#include "sdk/os/engine_halfb_api.h"
#include "sdk/pm/pm.h"

#define REG_IME (*(volatile u16 *)0x4000208)
#define REG_IF (*(volatile u32 *)0x4000214)

// Puts the console to sleep: runs the pre-sleep callbacks, switches the LCD and backlight off, tells the ARM7 to start
// the sleep and halts until it replies; after waking up (or when the cartridge was pulled out) restores the display
// and runs the post-sleep callbacks.
void PM_GoSleepMode(u32 trigger, u32 logic, u32 keyTrigger) {
    s32 forcePowerOff = 0;
    volatile u32 *dispcntA = (volatile u32 *)0x4000000;
    volatile u32 *dispcntB = (volatile u32 *)0x4001000;
    u16 imeOn = 1;
    u32 savedIrq;
    u32 savedMask;
    s32 lcdPower;
    u32 backlightTop;
    u32 backlightBottom;
    u32 savedDispcntA;
    u32 savedDispcntB;
    u16 ime;
    u32 sleepFlags;
    u32 backlightFlag;
    u32 wakeFlags;

    PMi_ExecuteList(data_0212b920.preExitList);
    ime = REG_IME;
    REG_IME = 0;
    savedIrq = OS_DisableInterrupts();
    savedMask = OS_DisableIrqMask(0xffffffff);
    OS_SetIrqMask((Engine_ReadHalfB() ? 8 : 0) | 0x40000);
    OS_RestoreInterrupts(savedIrq);
    REG_IME;
    REG_IME = imeOn;
    if (trigger & 8) {
        if ((u16)(OS_GetBootType() + 0xfffe) <= 1) {
            trigger &= ~8;
        }
    }
    if (trigger & 0x10) {
        trigger &= ~0x10;
    }
    savedDispcntA = *dispcntA;
    savedDispcntB = *dispcntB;
    lcdPower = PM_GetLCDPower();
    while (PM_GetBackLight(&backlightTop, &backlightBottom) != 0) {
        OS_SpinWaitSysCycles(0x51d23);
    }
    while (PM_SetBackLight(2, 0) != 0) {
        OS_SpinWaitSysCycles(0x51d23);
    }
    PMi_WaitVBlank();
    *dispcntA &= ~0x30000;
    *dispcntB &= ~0x10000;
    PMi_WaitVBlank();
    PMi_WaitVBlank();
    PMi_PreSleepForDma();
    data_0212b920.unk_08 = 0;
    sleepFlags = backlightBottom ? 0x80 : 0;
    backlightFlag = backlightTop ? 0x40 : 0;
    OS_SetIrqMask(0x40000);
    wakeFlags = trigger | backlightFlag;
    PMi_SendSleepStart((u16)(wakeFlags | sleepFlags), (u16)(logic | keyTrigger));
    while (data_0212b920.unk_08 == 0) {
        OS_Halt();
    }
    sleepFlags = 0;
    OS_SetIrqMask((Engine_ReadHalfB() ? 8 : 0) | 0x40000);
    if (trigger & 8) {
        if (REG_IF & 0x100000) {
            forcePowerOff = 1;
        }
    }
    if (forcePowerOff == 0) {
        if (lcdPower == 1) {
            while (func_0201d314(1, 1, 1, 1) != 1) {
            }
        } else {
            while (PMi_SetSoundVolume(1) != 0) {
                OS_SpinWaitSysCycles(0x51d23);
            }
        }
        *dispcntA = savedDispcntA;
        *dispcntB = savedDispcntB;
    }
    OS_SpinWaitSysCycles(0x360000);
    REG_IME;
    REG_IME = sleepFlags;
    OS_SetIrqMask(savedMask);
    OS_RestoreInterrupts(savedIrq);
    REG_IME;
    REG_IME = ime;
    if (forcePowerOff) {
        PM_ForceToPowerOff();
    }
    PMi_ExecuteList(data_0212b920.postExitList);
}
