#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/device_flags_api.h"
#include "sdk/os/dc_cache.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/pxi/pxi_fifo.h"
#include "sdk/snd/snd_command.h"
#include "sdk/snd/snd_work.h"

// Command ids and flags of the SND command queue.
enum {
    SND_COMMAND_SHARED_WORK = 0x1d,
    SND_COMMAND_BLOCK = 1,
    SND_COMMAND_IMMEDIATE = 2
};

// SND_RecvCommandReply(flags) (0x0201b0f0): takes the oldest sent list back into the free list once the ARM7 has
// finished it. With the block flag it waits for that; otherwise it returns NULL when nothing is finished.
SndQueuedCommand *SND_RecvCommandReply(u32 flags) {
    u32 irq = OS_DisableInterrupts();
    SndQueuedCommand *list;
    SndQueuedCommand *last;

    if (flags & SND_COMMAND_BLOCK) {
        while (data_02129dac.finishedCount == SNDi_GetFinishedCommandTag()) {
            OS_RestoreInterrupts(irq);
            OS_SpinWaitSysCycles(50);
            irq = OS_DisableInterrupts();
        }
    } else if (data_02129dac.finishedCount == SNDi_GetFinishedCommandTag()) {
        OS_RestoreInterrupts(irq);
        return NULL;
    }
    list = data_02129dd0[data_02129dac.recvIndex];
    data_02129dac.recvIndex++;
    if (data_02129dac.recvIndex > 8) {
        data_02129dac.recvIndex = 0;
    }
    last = list;
    while (last->next != NULL) {
        last = last->next;
    }
    if (data_02129dac.freeTail != NULL) {
        data_02129dac.freeTail->next = list;
    } else {
        data_02129dac.freeList = list;
    }
    data_02129dac.freeTail = last;
    data_02129dac.sentCount--;
    data_02129dac.finishedCount++;
    OS_RestoreInterrupts(irq);
    return list;
}

// SND_AllocCommand(flags) (0x0201b1f0): takes a command record from the free list; when none is free and the block flag
// is set, flushes and waits for the ARM7 to give records back.
SndQueuedCommand *SND_AllocCommand(u32 flags) {
    SndQueuedCommand *command;

    if (!IsCommandAvailable()) {
        return NULL;
    }
    command = AllocCommand();
    if (command != NULL) {
        return command;
    }
    if (!(flags & SND_COMMAND_BLOCK)) {
        return NULL;
    }
    if (SND_CountWaitingCommand() > 0) {
        while (SND_RecvCommandReply(0) != NULL) {
        }
        command = AllocCommand();
        if (command != NULL) {
            return command;
        }
    } else {
        SND_FlushCommand(SND_COMMAND_BLOCK);
    }
    RequestCommandProc();
    do {
        SND_RecvCommandReply(SND_COMMAND_BLOCK);
        command = AllocCommand();
    } while (command == NULL);
    return command;
}

// SND_PushCommand(command) (0x0201b278): appends a filled command record to the reserved list.
void SND_PushCommand(void *command) {
    SndQueuedCommand *newCommand = (SndQueuedCommand *)command;
    u32 irq = OS_DisableInterrupts();

    if (data_02129dac.reserveTail == NULL) {
        data_02129dac.reserveHead = newCommand;
        data_02129dac.reserveTail = newCommand;
        newCommand->next = NULL;
    } else {
        data_02129dac.reserveTail->next = newCommand;
        data_02129dac.reserveTail = newCommand;
        newCommand->next = NULL;
    }
    OS_RestoreInterrupts(irq);
}

