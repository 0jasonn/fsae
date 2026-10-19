#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   TelopRequest

// Telop request block (data_0217d36c)
typedef struct TelopWork {
    /* 00 */ u8 active;
    /* 01 */ u8 unk_01;
    /* 02 */ u8 flags; // low nibble = 3 while a request is active, bits 4-5 = bank of (id - 1000) / 100
    /* 03 */ u8 unk_03[3];
    /* 06 */ u16 requestId; // bit 15 is set while the telop is busy
} TelopWork;

extern TelopWork data_0217d36c;


typedef struct { u16 ids[8]; } TelopIdList;
extern const TelopIdList data_020d7c50 = { { 1001, 1101, 1201, 1301, 1302, 1303, 1006, 1009 } };

ARM void TelopRequest(u16 telopId) {
    TelopIdList list = data_020d7c50;

    u32 i;
    int found = 0;
    u8 bank;

    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        for (i = 0; i < 8; i++) {
            if (telopId == list.ids[i]) {
                telopId = (u16)(telopId + 0x1f4);
                found = 1;
                break;
            }
        }
    }
    if (data_0217d36c.requestId & 0x8000) {
        return;
    }
    func_02029a50(&data_0217d36c, 0x18);
    data_0217d36c.active = 1;
    data_0217d36c.requestId = telopId;
    data_0217d36c.flags = (data_0217d36c.flags & ~0xf) | 3;
    telopId &= 0x7fff;
    if (found) {
        telopId = (u16)(telopId - 0x1f4);
    }
    bank = (u8)((s32)(telopId - 1000) / 100);
    data_0217d36c.flags = (data_0217d36c.flags & ~0x30) | ((bank & 3) << 4);
}
