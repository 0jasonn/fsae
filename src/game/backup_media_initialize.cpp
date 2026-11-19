#include "engine/functions.h"
#include "engine/backup_media.h"
#include "game/rankingsave.h"
#include "game/backup.h"
#include "game/savemedia.h"
#include "global.h"

BOOL BackupMediaInitialize(void) {
    const SaveEepInfo *info;
    s32 status;
    s32 firstStatus;
    s32 result;

    firstStatus = Knife_loadSaveFile(1);
    if (firstStatus == 0 && SAVE_LOAD_STATE.fileLength == 0x800) {
        info = getEepInfo(3);
        if (Knife_mediaVerify(*(u16 *)&info->unk_04[2], data_020d852c, *(u16 *)info->unk_00) == 0) {
            SAVE_LOAD_RESULT = FSResultToKnifeFsResult(firstStatus);
            return TRUE;
        }
    }
    status = Knife_loadSaveFile(2);
    if (status == 0 && SAVE_LOAD_STATE.fileLength == 0x800) {
        info = getEepInfo(3);
        if (Knife_mediaVerify(*(u16 *)&info->unk_04[2], data_020d852c, *(u16 *)info->unk_00) == 0) {
            SAVE_LOAD_RESULT = FSResultToKnifeFsResult(status);
            Knife_mediaWrite();
            return TRUE;
        }
    }
    result = FSResultToKnifeFsResult(status);
    SAVE_LOAD_RESULT = result;
    if (result == 3 || (u32)result == 4) {
        return FALSE;
    }
    {
        BOOL notInitial;

        notInitial = FALSE;
        if (status != 0xb) {
            notInitial = TRUE;
        }
        if (status == 0xb) {
            status = Knife_InitialSaveFileALL();
        }
        SAVE_LOAD_RESULT = FSResultToKnifeFsResult(status);
        if (notInitial) {
            SAVE_LOAD_RESULT = 1;
            return FALSE;
        }
    }
    return TRUE;
}
