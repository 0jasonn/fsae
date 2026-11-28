#include "global.h"
#include "types.h"
#include "sdk/card/card.h"
#include "engine/functions.h"
#include "sdk/os/os_boot.h"
#include "sdk/os/os_lock.h"
#include "sdk/fs/fs_path.h"
#include "sdk/fs/fs_rom.h"
#include "sdk/fs/ret_const_api.h"
#include "sdk/fs/fs_rom.h"
#include "sdk/fs/fs_archive.h"
#include "sdk/card/card.h"
#include "engine/functions.h"

void FSi_InitRomArchive(u32 dmaNo) {
    FsCardHeaderTables *headerFat;
    FsCardHeaderTables *headerFnt;
    s32 mounted;

    CARD_Init();
    data_021297b8.dmaNo = dmaNo;
    data_021297b8.value = OS_GetLockID();
    FS_InitArchive(&data_021297c0);
    func_0200fd08(&data_021297c0, data_020dfb70, 3);
    if (OS_GetBootType() == 1) {
        headerFnt = (FsCardHeaderTables *)CARD_GetOwnRomHeader();
        headerFat = (FsCardHeaderTables *)CARD_GetOwnRomHeader();
        FS_SetArchiveProc(&data_021297c0, (void *)FsRom_Command, 0x682);
        if (headerFnt->fntOffset != 0xffffffff && headerFnt->fntOffset != 0 && headerFat->fatOffset != 0xffffffff &&
            headerFat->fatOffset != 0) {
            FS_LoadArchive(&data_021297c0, 0, headerFat->fatOffset, headerFat->fatSize, headerFnt->fntOffset,
                           headerFnt->fntSize, FSi_ReadRomCallback, NULL);
        }
    } else {
        func_02005470(&data_021297c0);
    }
    mounted = (data_021297c0.flag & 2) != 0;
    if (!mounted) {
        FS_SetArchiveProc(&data_021297c0, (void *)Obj_CodeForArg, 0xffffffff);
        FS_LoadArchive(&data_021297c0, 0, 0, 0, 0, 0, (FSArchiveAccessFunc)Stub_ReturnFourA, (FSArchiveAccessFunc)Stub_ReturnFourB);
    }
    FS_SetCurrentDirectory(data_020dfb74);
}
