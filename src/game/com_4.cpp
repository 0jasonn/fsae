#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/com_sio.h"

// Functions in this file (module com, original names from the debug build): com_machiuke (com_machiuke())

extern u8 data_0212c9a8[];   // communication state block (see com.cpp)
extern u32 opTitleState;
extern u8 localPlayerIndex;

void entry_check(void);                  // entry_check, parked in scratch/agentB/nonmatching
void cockpit_error_check(void);          // in com_3.cpp

// com_machiuke (0x02028280): the state machine of the communication handshake, run by the state byte 1 (cases 0..5).
ARM void com_machiuke(void) {
    u8 state;
    u8 sel;
    u8 flags;
    void *kn;

    func_020909c8();
    kn = KnifeApp_getInstance();
    data_0212c9a8[0x10] = 0x20;
    *(u16 *)(data_0212c9a8 + 0x12) = 0xffff;
    state = data_0212c9a8[1];
    switch (state) {
    case 0:
        data_0212c9a8[3] = 0;
        if (opTitleState & 0x100) {
            data_0212c9a8[1] = state + 1;
        } else {
            MultiSioStart();
        }
        break;
    case 1:
        data_0212c9a8[2] = 0x14;
        data_0212c9a8[1] = state + 1;
        break;
    case 2:
        data_0212c9a8[2] -= 1;
        if (data_0212c9a8[2] == 0) {
            MultiSioStart();
            data_0212c9a8[2] = 0x14;
            data_0212c9a8[1] += 1;
        }
        break;
    case 3:
        data_0212c9a8[2] -= 1;
        if (data_0212c9a8[2] == 0) {
            data_0212c9a8[1] = state + 1;
        }
        break;
    case 4:
        data_0212c9a8[0x10] = 0x21;
        data_0212c9a8[3] = opTitleState & 0xf;
        if (CommStatusSync(0x21) != 0) {
            if (data_0212c9a8[2] > 0x14) {
                sel = data_0212c9a8[3] & 0xf;
                if (sel == 3 || sel == 7 || sel == 0xf) {
                    data_0212c9a8[0x11] = 1;
                }
            } else {
                data_0212c9a8[2] += 1;
            }
        } else {
            data_0212c9a8[2] = 0;
            data_0212c9a8[3] |= 1 << localPlayerIndex;
        }
        flags = data_0212c9a8[3];
        sel = flags & 0xf;
        if (sel == 3) {
            if (data_0212c9a8[0x79] == 1 && data_0212c9a8[0xad] == 1) {
                data_0212c9a8[3] = flags | 0x40;
                data_0212c9a8[1] += 1;
            }
        } else if (sel == 7) {
            if (data_0212c9a8[0x79] == 1 && data_0212c9a8[0xad] == 1 && data_0212c9a8[0xe1] == 1) {
                data_0212c9a8[3] = flags | 0x40;
                data_0212c9a8[1] += 1;
            }
        } else if (sel == 0xf) {
            if (data_0212c9a8[0x79] == 1 && data_0212c9a8[0xad] == 1 && data_0212c9a8[0xe1] == 1 && data_0212c9a8[0x115] == 1) {
                data_0212c9a8[3] = flags | 0x40;
                data_0212c9a8[1] += 1;
            }
        }
        if (KnifeApp_isWirelessMode(kn) == 0) {
            data_0212c9a8[3] |= 0x43;
            data_0212c9a8[1] += 1;
        }
        cockpit_error_check();
        break;
    case 5:
        entry_check();
        cockpit_error_check();
        break;
    default:
        break;
    }
    data_0212c9a8[0x78] = 0;
    data_0212c9a8[0xac] = 0;
    data_0212c9a8[0xe0] = 0;
    data_0212c9a8[0x114] = 0;
}
