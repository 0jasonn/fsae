#include "engine/functions.h"
// Implementer B, round 4: encnt_getpos (0x02043b54).

#include "enemy/encnt.h"
#include "global.h"

ARM void encnt_getpos(void) {
    if (encntSharedState[0] == 0) {
        nextset();
        return;
    }
    u16 i;
    for (i = 0; i < encntState.limit; i++) {
        encntPosFuncs[encntState.kind](&encntEntries[i], i);
    }
    encntState.timer--;
    if (encntState.timer == 0) {
        encntState.count++;
        encntState.timer = 0x31;
    }
}
