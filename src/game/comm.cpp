#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "enemy/comm_check.h"
// Module comm (communication key handling). Address -> name:
//   0x020296e8 CommKeyCheck, 0x02029788 CommJoyCheck
// (CommUpdateJoy at 0x02029650 is parked in scratch/agentB/nonmatching.)

// Returns the 1-based index of the first slot whose key mask contains all of the keys, 0 when there is none.
ARM s32 CommKeyCheck(u16 keys) {
    if (data_0212c58c[0] != 0xffff) {
        if (keys == (keys & data_0212c58c[0])) {
            return 1;
        }
    }
    if (data_0212c58c[1] != 0xffff) {
        if (keys == (keys & data_0212c58c[1])) {
            return 2;
        }
    }
    if (data_0212c58c[2] != 0xffff) {
        if (keys == (keys & data_0212c58c[2])) {
            return 3;
        }
    }
    if (data_0212c58c[3] != 0xffff) {
        if (keys == (keys & data_0212c58c[3])) {
            return 4;
        }
    }
    return 0;
}

// Same as CommKeyCheck on the joypad slots (data_0212c584).
ARM s32 CommJoyCheck(u16 keys) {
    if (data_0212c584[0] != 0xffff) {
        if (keys == (keys & data_0212c584[0])) {
            return 1;
        }
    }
    if (data_0212c584[1] != 0xffff) {
        if (keys == (keys & data_0212c584[1])) {
            return 2;
        }
    }
    if (data_0212c584[2] != 0xffff) {
        if (keys == (keys & data_0212c584[2])) {
            return 3;
        }
    }
    if (data_0212c584[3] != 0xffff) {
        if (keys == (keys & data_0212c584[3])) {
            return 4;
        }
    }
    return 0;
}
