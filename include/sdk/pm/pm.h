#ifndef SDK_PM_PM_H
#define SDK_PM_PM_H

// TwlSDK PM library (pm.c): requests to the ARM7 power manager over the PXI FIFO (tag 8), LCD power and the callback
// lists.
#include "types.h"

typedef void (*PMiCallback)(u32 result, u32 arg); // TwlSDK PM callback

// PM library work at data_0212b920 (0x40 bytes).
typedef struct PmState {
    u16 ready;            // 0x00: PMi_InitSend has run
    u16 pad_02;           // 0x02
    void *postExitList;   // 0x04: callback list head (dsd: data_0212b924)
    u32 unk_08;           // 0x08: set to 1 by PXI reply 0x63
    u32 unk_0c;           // 0x0c: VBlank count (0x02fffc3c) when the LCD was last switched off
    u32 unk_10;           // 0x10: VBlank count when the display was switched off (PMi_SetDispOffCount)
    u32 lcdPowerState;    // 0x14: set to 3 when a forced power off starts
    u32 unk_18;           // 0x18: amplifier setting restored when the LCD is switched on
    void *preExitList;    // 0x1c: callback list head (dsd: data_0212b93c)
    u32 savedDmaControl[4]; // 0x20: DMA control words saved by PMi_PreSleepForDma (dsd: data_0212b940)
    s32 busy;             // 0x30: a request is in flight (dsd: data_0212b950)
    PMiCallback callback; // 0x34: run with the reply
    u32 callbackArg;      // 0x38
    u16 *retValue;        // 0x3c: receives the payload of a utility command reply
} PmState;

extern PmState data_0212b920;

// Symbols dsd gives to words inside data_0212b920; the code that reaches them directly uses these.
extern void *data_0212b924;         // postExitList: appended to by PM_AppendPostExitCallback
extern void *data_0212b93c;         // preExitList: prepended to by PM_PrependPostExitCallback, insertion by priority
                                    // in WBT_MpChildSendHook
extern u32 data_0212b940[4];        // savedDmaControl: the DMA channel control words before sleep
extern volatile u32 data_0212b950;  // busy: non-zero while a PM request is in flight

// How PMi_WaitBusy waits (TwlSDK wait-busy method): bit 1 polls the PXI FIFO while in IRQ mode, bit 2 while IRQs are
// masked in the CPSR, bit 3 while the interrupt master is off.
extern volatile u32 data_020dfbe4;

// Head of the callback list PM_ForceToPowerOffAsync runs. It lies outside the ARM9 image (no dsd symbol), so it is
// reached through its address.
#define PM_FORCE_OFF_CALLBACK_LIST (*(void **)0x021bfaf0)

extern "C" {
void PMi_DummyCallback(u32 result, u32 *out);
void PMi_RunCallback(u32 result);
void PMi_WaitBusy(void);
void PMi_WaitVBlank(void);
s32 PMi_StartSendBlock(u32 *words, s32 count, u32 a, u32 b, u32 c);
s32 PMi_SendSleepStart(u32 mode, u32 param);
s32 PM_SendUtilityCommandAsync(u32 number, u32 parameter, u16 *retValue, PMiCallback callback, u32 arg);
s32 PM_SendUtilityCommand(u32 number, u32 parameter, u16 *retValue);
s32 PMi_SetLEDAsync(u32 value, PMiCallback callback, u32 arg);
s32 PMi_SetSoundVolume(u32 value);
s32 PM_SetBackLightAsync(u32 target, u32 on, PMiCallback callback, u32 arg);
s32 PM_SetBackLight(u32 target, u32 on);
s32 PM_ForceToPowerOffAsync(PMiCallback callback, u32 arg);
s32 PMi_ForceToPowerOff(void);
s32 PMi_SetAmp(u32 enabled);
s32 PM_GetBackLight(u32 *top, u32 *bottom);
void PMi_SendPxiData(u32 word);
s32 func_0201d314(s32 mode, u32 value, s32 force, s32 useSound); // applies the PM sound, LED and amplifier state
s32 PM_SetLCDPower(s32 on);
s32 PM_GetLCDPower(void);
void PMi_InsertList(void **list, void *item, s32 priority, s32 prepend);
void PMi_DeleteList(void **list, void *item);
void PMi_ExecuteList(void *list);
void PMi_LCDOnAvoidReset(void);
void PMi_SetDispOffCount(void);
void PM_PrependPostExitCallback(void *item);
void PM_AppendPostExitCallback(void *item);
void WBT_MpChildSendHook(void *item, s32 priority);
void PmList_DeleteFirst(void *item);
void PmList_DeleteSecond(void *item);

void PM_ForceToPowerOff(void);
void PM_GoSleepMode(u32 trigger, u32 logic, u32 keyTrigger);
void PMi_PreSleepForDma(void);

// Outside the ARM9 image (linker symbols needed): called by PM_ForceToPowerOff after the timers are stopped, and by
// PMi_PreSleepForDma for each DMA channel.
void func_021894e4(void);
void func_0218a6b0(u32 dmaNo);

// Not decompiled yet.
void PMi_TryToSendPxiDataTillSuccess(u32 *words, s32 count);
}

#endif
