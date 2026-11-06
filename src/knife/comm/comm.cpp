#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "actor/enemy/comm_check.h"
// Module comm (communication key handling). Address -> name:
//   0x020296e8 CommKeyCheck, 0x02029788 CommJoyCheck
// (CommUpdateJoy at 0x02029650 is parked in scratch/agentB/nonmatching.)

// Returns the 1-based index of the first slot whose key mask contains all of the keys, 0 when there is none.
s32 CommKeyCheck(u16 keys) {
    if (playerKeys[0] != 0xffff) {
        if (keys == (keys & playerKeys[0])) {
            return 1;
        }
    }
    if (playerKeys[1] != 0xffff) {
        if (keys == (keys & playerKeys[1])) {
            return 2;
        }
    }
    if (playerKeys[2] != 0xffff) {
        if (keys == (keys & playerKeys[2])) {
            return 3;
        }
    }
    if (playerKeys[3] != 0xffff) {
        if (keys == (keys & playerKeys[3])) {
            return 4;
        }
    }
    return 0;
}

// Same as CommKeyCheck on the joypad slots (playerKeysPrev).
s32 CommJoyCheck(u16 keys) {
    if (playerKeysPrev[0] != 0xffff) {
        if (keys == (keys & playerKeysPrev[0])) {
            return 1;
        }
    }
    if (playerKeysPrev[1] != 0xffff) {
        if (keys == (keys & playerKeysPrev[1])) {
            return 2;
        }
    }
    if (playerKeysPrev[2] != 0xffff) {
        if (keys == (keys & playerKeysPrev[2])) {
            return 3;
        }
    }
    if (playerKeysPrev[3] != 0xffff) {
        if (keys == (keys & playerKeysPrev[3])) {
            return 4;
        }
    }
    return 0;
}
