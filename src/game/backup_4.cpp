#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"

// Save media unit 4. Address -> name:
//   0x02056e1c Knife_checkFileSpace (provisional)
//   0x02056e70 FSResultToKnifeFsResult (original name)
//   0x02056ee0 Knife_getSaveBuffer (provisional)

ARM s32 Knife_checkFileSpace(s32 fileSize, const char *path) {
    u8 resource[0x30];

    if (FS_GetArchiveResource(path, resource) == 0) {
        return 10;
    }
    if (FS_HasEnoughSpaceToCreateFile(resource, path, fileSize) != 0) {
        return 0;
    }
    return 7;
}

ARM s32 FSResultToKnifeFsResult(s32 result) {
    switch (result) {
    case 0:
        return 0;
    case 14:
        return 3;
    case 10:
        return 4;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 11:
    case 12:
    case 13:
        return 1;
    }
    return 1;
}

ARM void *Knife_getSaveBuffer(void) {
    return data_02171d10;
}
