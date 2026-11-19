#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/commerror.h"

// Communication error module (0x02029828 to 0x02029968): CommStatusSync, comerror_error_check.
// comWork is the communication state block: byte 0x03 holds the ready mask of the players (low 4 bits),
// u16 0x0c the error timer, byte 0x0e a hold flag, and four 0x34-byte player slots from 0x78 whose first byte is a tag.
// opTitleState holds the connection bits of the four players.

#include "engine/com_work.h"
extern u8 data_0212c4d4;
extern u32 opTitleState;

// CommStatusSync (0x02029828): 1 when every connected player's tag equals status, matching the ready mask.
int CommStatusSync(u8 status) {
    u8 matched;
    u8 expected;
    u32 connected;

    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        return 1;
    }
    expected = comWork.status & 0xf;
    connected = opTitleState;
    matched = 0;
    if (connected & 1) {
        if (comWork.recv[0].tag == status) {
            matched |= 1;
        }
    }
    if (connected & 2) {
        if (comWork.recv[1].tag == status) {
            matched |= 2;
        }
    }
    if (connected & 4) {
        if (comWork.recv[2].tag == status) {
            matched |= 4;
        }
    }
    if (connected & 8) {
        if (comWork.recv[3].tag == status) {
            matched |= 8;
        }
    }
    return matched == expected;
}

// comerror_error_check (0x020298d0): as CommStatusSync, and the connection bits must equal the matched players.
int comerror_error_check(u8 value) {
    u8 matched = 0;
    u8 expected;
    u32 connected;

    expected = comWork.status & 0xf;
    connected = opTitleState;
    if (connected & 1) {
        if (comWork.recv[0].tag == value) {
            matched |= 1;
        }
    }
    if (connected & 2) {
        if (comWork.recv[1].tag == value) {
            matched |= 2;
        }
    }
    if (connected & 4) {
        if (comWork.recv[2].tag == value) {
            matched |= 4;
        }
    }
    if (connected & 8) {
        if (comWork.recv[3].tag == value) {
            matched |= 8;
        }
    }
    return matched == expected && (connected & 0xf) == matched;
}
