#include "engine/functions.h"
#include "global.h"

// Rupee level and the error message, 0x02082054 to 0x020820cc.
//   getRupeeLevel (0x02082054): maps the rupee count (game state word at +8) to a level 0 to 3.
//   rupee_error (0x02082094): requests the message, sets the two display bytes of messageRequest, then goto_nextdemo.

#include "engine/player.h"

extern u8 messageRequest[];
void goto_nextdemo(void);

// getRupeeLevel (0x02082054)
ARM int getRupeeLevel(void) {
    u32 rupees;

    rupees = *(u32 *)((u8 *)&data_0212c7c8 + 8);
    if (rupees < 1000) {
        return 0;
    }
    if (rupees < 0xbb8) {
        return 1;
    }
    if (rupees < 0x1388) {
        return 2;
    }
    return 3;
}

// rupee_error (0x02082094)
ARM void rupee_error(u16 message) {
    MessageRequest(message);
    messageRequest[3] = (messageRequest[3] & ~0x1f) | 1;
    messageRequest[4] = (messageRequest[4] & ~0x1f) | 0xe;
    goto_nextdemo();
}
