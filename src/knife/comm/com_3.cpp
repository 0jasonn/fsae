#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/comm/com_sio.h"

// Functions in this file (module com, original names from the debug build): cockpit_error_check (error_check())

extern u8 comWork[];   // communication state block (see com.cpp)
extern u32 opTitleState;

// cockpit_error_check (0x020281b0): when the error state in opTitleState says so, resets the serial and the state bytes
// 1 and 3. Wireless play resets whenever bit 0x1000 is set; otherwise bit 0x8000 and the two nibbles must match first.
void cockpit_error_check(void) {
    u32 state;

    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        state = opTitleState;
        if ((state & 0x1000) == 0 && (state & 0x8000) != 0 && ((state >> 8) & 0xf) == (state & 0xf)) {
            return;
        }
        MultiSioStop();
        MultiSioInit();
        comWork[1] = 0;
        comWork[3] = 0;
    } else {
        if ((opTitleState & 0x1000) == 0) {
            return;
        }
        MultiSioStop();
        MultiSioInit();
        comWork[1] = 0;
        comWork[3] = 0;
    }
}
