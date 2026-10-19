// Implementer B, round 4: encounter controller, encnt_move (0x02043760).
// Address -> name: 0x02043760 encnt_move (matched). area_check (0x020438b4) and encnt_setinit (0x020439f4)
// are not matched yet; see scratch/agentB/nonmatching.

#include "enemy/encnt.h"
#include "global.h"

ARM void encnt_move(void) {
    if (data_021348ec[0] == 0) {
        return;
    }
    data_02134b48.timer--;
    if (data_02134b48.timer == 0) {
        if (GetVgRemain() >= 8 && data_021348e0 <= 4) {
            if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
                data_02134b48.entity = data_0212ceb0[(Random() % data_0212c7c8.unk_0) & 3].entity;
            } else {
                u32 idx = (Random() % data_0212c7c8.unk_0) & 3;
                if (data_0212c584[idx] & 0x1000) {
                    idx ^= 1;
                }
                data_02134b48.entity = data_0212ceb0[idx].entity;
            }
            int found = 1;
            if (!area_check(found)) {
                found = area_check(0);
            }
            if (found != 0) {
                data_02134b48.count++;
                return;
            }
            nextset();
            return;
        } else {
            nextset();
            return;
        }
    } else if (data_02134b48.timer == 1) {
        data_021348e0 = 0;
        data_0212c540 |= 4;
    }
}
