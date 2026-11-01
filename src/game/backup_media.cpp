#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/backup_media.h"

// Save media functions (module backup): ReadFromMedia (0x020562ec).

// ReadFromMedia(u8 slot, u32 *data) (0x020562ec): reads the save of a slot into data, trying slot 1 and then slot 2.
// Returns the load result code (also kept in the save load state).
s32 ReadFromMedia(u8 slot, u32 *data) {
    u32 header[2];
    const SaveEepInfo *info;
    BOOL retry;
    BOOL failed;
    s32 loadResult;
    s32 fatStatus;

    SAVE_LOAD_RESULT = 0;
    retry = FALSE;
    failed = FALSE;
    info = getEepInfo(slot);
    if (Knife_loadSaveFile(1) == 0) {
        fatStatus = Knife_fatRead(info->unk_02, (_SAVEHEADER *)header);
        switch (fatStatus) {
        case 0:
            readFromSaveBuffer(data, *(u16 *)&info->unk_04[2], *(u16 *)info->unk_00);
            if (isAccordData((_SAVEHEADER *)header, data, *(u16 *)info->unk_00) != 0) {
                SAVE_LOAD_RESULT = 0;
                return 0;
            }
            retry = TRUE;
            break;
        case 8:
            SAVE_LOAD_RESULT = 8;
            return 8;
        case 6:
            retry = TRUE;
            break;
        }
    }
    loadResult = Knife_loadSaveFile(2);
    if (loadResult == 0) {
        fatStatus = Knife_fatRead(info->unk_02, (_SAVEHEADER *)header);
        switch (fatStatus) {
        case 0:
            readFromSaveBuffer(data, *(u16 *)&info->unk_04[2], *(u16 *)info->unk_00);
            if (isAccordData((_SAVEHEADER *)header, data, *(u16 *)info->unk_00) != 0) {
                Knife_mediaWrite();
                SAVE_LOAD_RESULT = 0;
                return 0;
            }
            failed = TRUE;
            break;
        case 8:
            Knife_mediaWrite();
            SAVE_LOAD_RESULT = 8;
            return 8;
        case 6:
            failed = TRUE;
            break;
        }
    }
    OSi_CpuClear32(0, data, *(u16 *)info->unk_00);
    if (SAVE_LOAD_RESULT != 6) {
        SAVE_LOAD_RESULT = FSResultToKnifeFsResult(loadResult);
    }
    if (failed || retry) {
        SAVE_LOAD_RESULT = 6;
    }
    return SAVE_LOAD_RESULT;
}
