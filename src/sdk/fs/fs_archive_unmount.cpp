#include "global.h"
#include "types.h"
#include "sdk/fs/fs_archive.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_command.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/os/os_thread.h"
#include "sdk/card/card.h"

s32 FS_UnmountArchive(FSArchive *arc) {
    FSFile file;
    u32 irqState;
    s32 mounted;
    s32 suspended;
    FSFile *current;
    FSFile *next;

    irqState = OS_DisableInterrupts();
    mounted = (arc->flag & FS_ARCHIVE_FLAG_MOUNTED) != 0 ? 1 : 0;
    if (mounted != 0) {
        suspended = FS_SuspendArchive(arc);
        arc->flag |= FS_ARCHIVE_FLAG_UNMOUNTING;
        for (current = arc->list; current != NULL; current = next) {
            next = current->next;
            FSi_EndCommand(current, 3);
        }
        arc->list = NULL;
        if (suspended != 0) {
            FS_ResumeArchive(arc);
        }
        FS_InitFile(&file);
        file.arc = arc;
        func_0200f068(&file, 0x12);
        arc->flag &= ~(FS_ARCHIVE_FLAG_UNMOUNTING | FS_ARCHIVE_FLAG_YIELD | FS_ARCHIVE_FLAG_MOUNTED);
    }
    OS_RestoreInterrupts(irqState);
    return 1;
}

s32 FS_SuspendArchive(FSArchive *arc) {
    u32 irqState;
    u32 irqState2;
    s32 suspended;
    s32 result;

    irqState = OS_DisableInterrupts();
    suspended = (((volatile FSArchive *)arc)->flag & FS_ARCHIVE_FLAG_SUSPENDED) != 0 ? 1 : 0;
    result = 1;
    if (suspended != 0) {
        result = 0;
    }
    if (result != 0) {
        if ((arc->flag & FS_ARCHIVE_FLAG_RUNNING) == 0) {
            arc->flag |= FS_ARCHIVE_FLAG_SUSPENDED;
        } else {
            arc->flag |= FS_ARCHIVE_FLAG_SUSPENDING;
            irqState2 = OS_DisableInterrupts();
            while ((arc->flag & FS_ARCHIVE_FLAG_SUSPENDING) != 0) {
                Os_LinkThreadAndFlush(&arc->queue);
            }
            OS_RestoreInterrupts(irqState2);
        }
    }
    OS_RestoreInterrupts(irqState);
    return result;
}

s32 FS_ResumeArchive(FSArchive *arc) {
    u32 irqState;
    s32 result;
    s32 suspended;
    FSFile *next;

    irqState = OS_DisableInterrupts();
    suspended = (arc->flag & FS_ARCHIVE_FLAG_SUSPENDED) != 0 ? 1 : 0;
    result = 1;
    if (suspended != 0) {
        result = 0;
    }
    if (result == 0) {
        arc->flag &= ~FS_ARCHIVE_FLAG_SUSPENDED;
    }
    OS_RestoreInterrupts(irqState);
    next = FSi_NextCommand(arc, 1);
    if (next != NULL) {
        FSi_ExecuteAsyncCommand(next);
    }
    return result;
}

void FS_NotifyArchiveAsyncEnd(FSArchive *arc, s32 result) {
    FSFile *file;
    FSFile *next;
    u32 irqState;

    file = arc->list;
    if ((file->stat & FS_FILE_STAT_BLOCKING) != 0) {
        irqState = OS_DisableInterrupts();
        file->stat |= FS_FILE_STAT_DONE;
        file->error = result;
        OS_WakeupThread(&file->queue);
        OS_RestoreInterrupts(irqState);
        return;
    }
    FSi_EndCommand(file, result);
    next = FSi_NextCommand(arc, 1);
    if (next != NULL) {
        FSi_ExecuteAsyncCommand(next);
    }
}

s32 FS_WaitAsync(FSFile *file) {
    s32 blocking;
    u32 irqState;
    s32 busy;

    blocking = 0;
    irqState = OS_DisableInterrupts();
    busy = (file->stat & FS_FILE_STAT_BUSY) != 0 ? 1 : 0;
    if (busy != 0) {
        blocking = (((volatile FSFile *)file)->stat & (FS_FILE_STAT_BLOCKING | FS_FILE_STAT_READY)) == 0 ? 1 : 0;
        if (blocking != 0) {
            file->stat |= FS_FILE_STAT_BLOCKING;
        }
    }
    OS_RestoreInterrupts(irqState);
    if (blocking != 0) {
        FSi_ExecuteSyncCommand(file);
    } else {
        irqState = OS_DisableInterrupts();
        while ((file->stat & FS_FILE_STAT_BUSY) != 0) {
            Os_LinkThreadAndFlush(&file->queue);
        }
        OS_RestoreInterrupts(irqState);
    }
    return file->error == 0 ? 1 : 0;
}
