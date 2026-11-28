#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/snd/snd_command.h"

enum {
    SND_COMMAND_BLOCK = 1
};

// SND_WaitForCommandProc(tag) (0x0201b44c): blocks until the flush with this tag has been finished by the ARM7.
void SND_WaitForCommandProc(u32 tag) {
    if (SND_IsFinishedCommandTag(tag)) {
        return;
    }
    while (SND_RecvCommandReply(0) != NULL) {
    }
    if (SND_IsFinishedCommandTag(tag)) {
        return;
    }
    RequestCommandProc();
    if (SND_IsFinishedCommandTag(tag)) {
        return;
    }
    do {
        SND_RecvCommandReply(SND_COMMAND_BLOCK);
    } while (!SND_IsFinishedCommandTag(tag));
}

// SND_GetCurrentCommandTag() (0x0201b4b8): tag a command pushed now would be finished with.
u32 SND_GetCurrentCommandTag(void) {
    u32 irq = OS_DisableInterrupts();
    u32 tag;

    if (data_02129dac.reserveHead == NULL) {
        tag = data_02129dac.finishedCount;
    } else {
        tag = data_02129dac.sentTag;
    }
    OS_RestoreInterrupts(irq);
    return tag;
}

// SND_IsFinishedCommandTag(tag) (0x0201b4e4): whether the flush with this tag has been finished, comparing the tags
// modulo 2^32 (a tag counts as finished when it is at most 2^31 behind the finished counter).
s32 SND_IsFinishedCommandTag(u32 tag) {
    u32 irq = OS_DisableInterrupts();
    u32 finished = data_02129dac.finishedCount;
    s32 result;

    if (tag > finished) {
        if (tag - finished < 0x80000000) {
            result = 0;
        } else {
            result = 1;
        }
    } else {
        result = (finished - tag) < 0x80000000;
    }
    OS_RestoreInterrupts(irq);
    return result;
}

// SND_CountFreeCommand() (0x0201b534): number of command records in the free list.
s32 SND_CountFreeCommand(void) {
    u32 irq = OS_DisableInterrupts();
    SndQueuedCommand *command = data_02129dac.freeList;
    s32 count = 0;

    while (command != NULL) {
        command = command->next;
        count++;
    }
    OS_RestoreInterrupts(irq);
    return count;
}

// SND_CountReservedCommand() (0x0201b570): number of command records in the reserved list.
s32 SND_CountReservedCommand(void) {
    u32 irq = OS_DisableInterrupts();
    SndQueuedCommand *command = data_02129dac.reserveHead;
    s32 count = 0;

    while (command != NULL) {
        command = command->next;
        count++;
    }
    OS_RestoreInterrupts(irq);
    return count;
}

// SND_CountWaitingCommand() (0x0201b5ac): records that are neither free nor reserved, i.e. sent and not yet returned.
s32 SND_CountWaitingCommand(void) {
    s32 free = SND_CountFreeCommand();

    return 256 - free - SND_CountReservedCommand();
}
