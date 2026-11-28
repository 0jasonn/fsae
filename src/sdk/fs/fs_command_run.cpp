#include "global.h"
#include "types.h"
#include "sdk/fs/fs_archive.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_command.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/os/os_thread.h"
#include "sdk/card/card.h"

void FSi_ExecuteAsyncCommand(FSFile *file) {
    FSArchive *arc;
    u32 irqState;

    arc = file->arc;
    if (file == NULL) {
        return;
    }
    do {
        irqState = OS_DisableInterrupts();
        file->stat |= FS_FILE_STAT_READY;
        if ((file->stat & FS_FILE_STAT_BLOCKING) != 0) {
            OS_WakeupThread(&file->queue);
            file = NULL;
        }
        OS_RestoreInterrupts(irqState);
        if (file == NULL) {
            return;
        }
        if (func_0200f068(file, (file->stat >> FS_FILE_STAT_COMMAND_SHIFT) & 0xff) == 0x100) {
            return;
        }
        file = FSi_NextCommand(arc, 1);
    } while (file != NULL);
}

void FSi_ExecuteSyncCommand(FSFile *file) {
    FSArchive *arc;
    FSFile *next;
    u32 irqState;
    u32 command;

    irqState = OS_DisableInterrupts();
    while ((file->stat & FS_FILE_STAT_READY) == 0 && (file->stat & FS_FILE_STAT_BUSY) != 0) {
        Os_LinkThreadAndFlush(&file->queue);
    }
    OS_RestoreInterrupts(irqState);
    if ((((volatile FSFile *)file)->stat & FS_FILE_STAT_READY) != 0) {
        command = (file->stat >> FS_FILE_STAT_COMMAND_SHIFT) & 0xff;
        arc = file->arc;
        FSi_EndCommand(file, func_0200f068(file, command));
        next = FSi_NextCommand(arc, 1);
        if (next != NULL) {
            FSi_ExecuteAsyncCommand(next);
        }
    }
}
