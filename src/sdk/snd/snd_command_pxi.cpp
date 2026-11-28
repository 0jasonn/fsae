#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/device_flags_api.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/pxi/pxi_fifo.h"
#include "sdk/snd/snd_alarm.h"
#include "sdk/snd/snd_command.h"

// PxiFifoCallback(tag, data, err) (0x0201b5c8): receive handler of PXI tag 7; the payload is an alarm number.
void PxiFifoCallback(u32 tag, u32 data, s32 err) {
    u32 irq = OS_DisableInterrupts();

    SNDi_CallAlarmHandler(data);
    OS_RestoreInterrupts(irq);
}

// InitPXI() (0x0201b5ec): installs the sound PXI callback and, on hardware, waits until the ARM7 side is ready.
void InitPXI(void) {
    PXI_SetFifoRecvCallback(7, PxiFifoCallback);
    if (!IsCommandAvailable()) {
        return;
    }
    if (PXI_IsCallbackReady(7, 1)) {
        return;
    }
    do {
        OS_SpinWaitSysCycles(50);
    } while (!PXI_IsCallbackReady(7, 1));
}

// RequestCommandProc() (0x0201b650): asks the ARM7 to process the queue, retrying until the FIFO accepts the word.
void RequestCommandProc(void) {
    while (PXI_SendWordByFifo(7, 0, 0) < 0) {
    }
}

// AllocCommand() (0x0201b678): pops the first record off the free list; NULL when it is empty.
SndQueuedCommand *AllocCommand(void) {
    u32 irq = OS_DisableInterrupts();
    SndQueuedCommand *command = data_02129dac.freeList;
    SndQueuedCommand *next;

    if (command == NULL) {
        OS_RestoreInterrupts(irq);
        return NULL;
    }
    next = command->next;
    data_02129dac.freeList = next;
    if (next == NULL) {
        data_02129dac.freeTail = NULL;
    }
    OS_RestoreInterrupts(irq);
    return command;
}

// IsCommandAvailable() (0x0201b6c0): on hardware the command queue is always usable; on an emulator it probes a
// register of the memory-mapped sound interface and reports whether that responded.
BOOL IsCommandAvailable(void) {
    u32 irq;
    u32 value;

    if (!OS_IsRunOnEmulator()) {
        return TRUE;
    }
    irq = OS_DisableInterrupts();
    *(volatile u32 *)0x04fff200 = 0x10;
    value = *(volatile u32 *)0x04fff200;
    OS_RestoreInterrupts(irq);
    return value != 0;
}
