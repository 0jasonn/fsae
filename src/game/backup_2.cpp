#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"

// Save media (backup) unit 2. Address -> name:
//   0x020565e8 Knife_fatRead (original name, matches)

ARM s32 Knife_fatRead(u16 slot, _SAVEHEADER *header) {
    s32 result;

    readFromSaveBuffer((u32 *)header, slot, 8);
    result = checkFatData(header);
    switch (result) {
    case 0:
        return 6;
    case 1:
        return 8;
    case 2:
        return 0;
    }
    return result;
}
