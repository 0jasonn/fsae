#include "engine/functions.h"
#include "knife/comm/commframe_sync.h"

// CommFrameSync() (0x02028fe8): TRUE when the frames of the wireless players are in sync: always TRUE outside wireless
// mode, otherwise when the communication state word is 2 or the pending flag is set.
int CommFrameSync(void) {
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
        if (*(u32 *)(comWork + 8) == 2 || data_0212c4d4 != 0) {
            return 1;
        }
        return 0;
    }
    return 1;
}
