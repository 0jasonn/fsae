#include "engine/functions.h"
#include "global.h"
#include "game/b_extra.h"

// Owner language code, 0x02082838: reads the DS owner info (OS_GetOwnerInfoEx) and maps its language byte
// to a game language index (4 to 8; 4 for the default).

// GetOwnerLanguageCode (0x02082838), was GetOwnerLanguageCode
ARM s32 GetOwnerLanguageCode(void) {
    u8 ownerInfo[0x58];
    u8 language;

    OS_GetOwnerInfoEx(ownerInfo);
    language = ownerInfo[0];
    switch (language) {
    case 1:
        return 4;
    case 2:
        return 5;
    case 3:
        return 6;
    case 4:
        return 8;
    case 5:
        return 7;
    default:
        return 4;
    }
}
