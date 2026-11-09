#include "engine/functions.h"
#include "actor/object/knife_comm_skip.h"

// 0x0204b488 (original name, plain symbol). Message ids 100-199, 200-299 and 600-699 can be skipped.
int isSkipAvailable(KNIFE_MSGSYS *msg) {
    u16 id = msg->msgId;

    if ((id >= 100 && id <= 199) || (id >= 200 && id <= 299) || (id >= 600 && id <= 699)) {
        return 1;
    }
    return 0;
}
