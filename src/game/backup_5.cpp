#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"

// Save media unit 5. Address -> name:
//   0x02056998 Knife_InitialSaveFile (original name)

ARM void Knife_InitialSaveFile(u8 slot) {
    const u8 *name = data_020d8524;
    const SaveEepInfo *info;

    if ((slot & 0xc0) != 0) {
        return;
    }
    info = getEepInfo((u8)(slot | 4));
    func_020569cc(name, info->unk_02, 8);
}
