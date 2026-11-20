#include "engine/functions.h"
#include "engine/local_player_index.h"
#include "global.h"
#include "types.h"
#include "knife/comm/com_sio.h"

// Functions in this file (module com, original names from the debug build): com_machiuke (com_machiuke())

#include "engine/com_work.h"
#include "engine/entry_check.h"
extern u32 opTitleState;

void cockpit_error_check(void);          // in com_3.cpp

// com_machiuke (0x02028280): the state machine of the communication handshake, run by the state byte 1 (cases 0..5).
void com_machiuke(void) {
    u8 state;
    u8 sel;
    u8 flags;
    void *kn;

    func_020909c8();
    kn = KnifeApp_getInstance();
    comWork.send.tag = 0x20;
    comWork.send.keys = 0xffff;
    state = comWork.phase;
    switch (state) {
    case 0:
        comWork.status = 0;
        if (opTitleState & 0x100) {
            comWork.phase = state + 1;
        } else {
            MultiSioStart();
        }
        break;
    case 1:
        comWork.counter = 0x14;
        comWork.phase = state + 1;
        break;
    case 2:
        comWork.counter -= 1;
        if (comWork.counter == 0) {
            MultiSioStart();
            comWork.counter = 0x14;
            comWork.phase += 1;
        }
        break;
    case 3:
        comWork.counter -= 1;
        if (comWork.counter == 0) {
            comWork.phase = state + 1;
        }
        break;
    case 4:
        comWork.send.tag = 0x21;
        comWork.status = opTitleState & 0xf;
        if (CommStatusSync(0x21) != 0) {
            if (comWork.counter > 0x14) {
                sel = comWork.status & 0xf;
                if (sel == 3 || sel == 7 || sel == 0xf) {
                    comWork.send.ready = 1;
                }
            } else {
                comWork.counter += 1;
            }
        } else {
            comWork.counter = 0;
            comWork.status |= 1 << localPlayerIndex;
        }
        flags = comWork.status;
        sel = flags & 0xf;
        if (sel == 3) {
            if (comWork.recv[0].ready == 1 && comWork.recv[1].ready == 1) {
                comWork.status = flags | 0x40;
                comWork.phase += 1;
            }
        } else if (sel == 7) {
            if (comWork.recv[0].ready == 1 && comWork.recv[1].ready == 1 && comWork.recv[2].ready == 1) {
                comWork.status = flags | 0x40;
                comWork.phase += 1;
            }
        } else if (sel == 0xf) {
            if (comWork.recv[0].ready == 1 && comWork.recv[1].ready == 1 && comWork.recv[2].ready == 1 && comWork.recv[3].ready == 1) {
                comWork.status = flags | 0x40;
                comWork.phase += 1;
            }
        }
        if (KnifeApp_isWirelessMode(kn) == 0) {
            comWork.status |= 0x43;
            comWork.phase += 1;
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
    comWork.recv[0].tag = 0;
    comWork.recv[1].tag = 0;
    comWork.recv[2].tag = 0;
    comWork.recv[3].tag = 0;
}
