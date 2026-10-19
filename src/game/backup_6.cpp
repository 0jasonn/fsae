#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"

// Save media (backup) unit. Address -> name:
//   0x02056120 CalcChecksum (original name)
//   0x0205614c Knife_writeMediaFlagged -> Knife_writeMediaFlagged (provisional)
//   0x02056160 Knife_readMediaFlagged -> Knife_readMediaFlagged (provisional)
//   0x02056174 Knife_writeHeaderBlock -> Knife_writeHeaderBlock (provisional)
//   0x02056188 ReadCartInfo (original name)
//   0x020561a4 DeleteSaveFile (original name)

ARM const SaveEepInfo *getEepInfo(u8 slot) {
    return &data_020d8550[slot & 7];
}
