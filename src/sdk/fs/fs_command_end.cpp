#include "global.h"
#include "types.h"
#include "sdk/fs/fs_archive.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_command.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/os/os_thread.h"
#include "sdk/card/card.h"

s32 FSi_IsEventCommand(u32 command) {
    s32 result;
    u32 index;
    u32 bit;

    result = 0;
    index = command - 9;
    if (index <= 0x1a) {
        bit = 1;
        if ((0x400030f & (bit << index)) != 0) {
            result = bit;
        }
    }
    return result;
}

void FSi_EndCommand(FSFile *file, s32 result) {
    u32 irqState;
    FSArchive *arc;
    FSFile *current;
    FSFile **link;
    u32 command;

    irqState = OS_DisableInterrupts();
    arc = file->arc;
    if (arc != NULL) {
        link = &arc->list;
        for (current = arc->list; current != NULL; current = current->next) {
            if (current == file) {
                *link = file->next;
                break;
            }
            link = &current->next;
        }
        file->next = NULL;
    }
    command = (file->stat >> FS_FILE_STAT_COMMAND_SHIFT) & 0xff;
    if (FSi_IsEventCommand(command) == 0 && arc != NULL) {
        arc->lastCommand = command;
        arc->lastResult = result;
    }
    file->error = result;
    file->stat &= ~0xcf;
    OS_WakeupThread(&file->queue);
    OS_RestoreInterrupts(irqState);
}

s32 FSi_WaitForArchiveCompletion(FSFile *file, s32 result) {
    u32 irqState;

    if (result == 0x100) {
        irqState = OS_DisableInterrupts();
        while ((file->stat & FS_FILE_STAT_DONE) == 0) {
            Os_LinkThreadAndFlush(&file->queue);
        }
        OS_RestoreInterrupts(irqState);
        result = file->error;
        file->stat &= ~FS_FILE_STAT_DONE;
    }
    return result;
}
