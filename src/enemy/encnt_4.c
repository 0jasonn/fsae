// Implementer B, round 4: encnt_getpos (0x02043b54).

#include "enemy/encnt.h"
#include "global.h"

ARM void encnt_getpos(void) {
    if (data_021348ec[0] == 0) {
        nextset();
        return;
    }
    u16 i;
    for (i = 0; i < data_02134b48.limit; i++) {
        data_020d4150[data_02134b48.kind](&data_02134b60[i], i);
    }
    data_02134b48.timer--;
    if (data_02134b48.timer == 0) {
        data_02134b48.count++;
        data_02134b48.timer = 0x31;
    }
}
