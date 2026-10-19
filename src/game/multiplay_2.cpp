#include "engine/functions.h"
#include "game/multiplay.h"
#include "global.h"

ARM void multiplay_sync(void) {
    switch (data_0212c4dc) {
    case 0:
        ComRequest(4);
        data_0212c4dc++;
        break;
    case 1:
        if (WXC_GetStateCode() != 1) {
            return;
        }
        data_0212c554 = data_0212c550;
        data_0212c500++;
        data_0212c4dc = 0;
        break;
    }
}

ARM void multiplay_makemap(void) {
    multiplayMakemapTable[data_0212c4dc]();
}
