#include "engine/functions.h"
#include "global.h"
#include "enemy/commerror.h"

// Communication error module (0x02029828 to 0x02029968): CommStatusSync, comerror_error_check.
// data_0212c9a8 is the communication state block: byte 0x03 holds the ready mask of the players (low 4 bits),
// u16 0x0c the error timer, byte 0x0e a hold flag, and four 0x34-byte player slots from 0x78 whose first byte is a tag.
// opTitleState holds the connection bits of the four players.

typedef struct ComPlayerSlot {
    u8 tag;          // 00: status code that the player reports
    u8 unk_01[0x33];
} ComPlayerSlot;

typedef struct ComErrorWork {
    u8 unk_00[3];
    u8 readyMask;    // 03
    u8 unk_04[8];
    u16 errorTimer;  // 0c
    u8 holdFlag;     // 0e
    u8 unk_0f[0x78 - 0x0f];
    ComPlayerSlot players[4];
} ComErrorWork;

#define COM_WORK ((ComErrorWork *)data_0212c9a8)

extern u8 data_0212c9a8[];
extern u8 data_0212c4d4;
extern u32 opTitleState;

// CommStatusSync (0x02029828): 1 when every connected player's tag equals status, matching the ready mask.
ARM int CommStatusSync(u8 status) {
    u8 matched;
    u8 expected;
    u32 connected;

    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        return 1;
    }
    expected = COM_WORK->readyMask & 0xf;
    connected = opTitleState;
    matched = 0;
    if (connected & 1) {
        if (COM_WORK->players[0].tag == status) {
            matched |= 1;
        }
    }
    if (connected & 2) {
        if (COM_WORK->players[1].tag == status) {
            matched |= 2;
        }
    }
    if (connected & 4) {
        if (COM_WORK->players[2].tag == status) {
            matched |= 4;
        }
    }
    if (connected & 8) {
        if (COM_WORK->players[3].tag == status) {
            matched |= 8;
        }
    }
    return matched == expected;
}

// comerror_error_check (0x020298d0): as CommStatusSync, and the connection bits must equal the matched players.
extern "C" int comerror_error_check(u8 value);
ARM int comerror_error_check(u8 value) {
    u8 matched = 0;
    u8 expected;
    u32 connected;

    expected = COM_WORK->readyMask & 0xf;
    connected = opTitleState;
    if (connected & 1) {
        if (COM_WORK->players[0].tag == value) {
            matched |= 1;
        }
    }
    if (connected & 2) {
        if (COM_WORK->players[1].tag == value) {
            matched |= 2;
        }
    }
    if (connected & 4) {
        if (COM_WORK->players[2].tag == value) {
            matched |= 4;
        }
    }
    if (connected & 8) {
        if (COM_WORK->players[3].tag == value) {
            matched |= 8;
        }
    }
    return matched == expected && (connected & 0xf) == matched;
}
