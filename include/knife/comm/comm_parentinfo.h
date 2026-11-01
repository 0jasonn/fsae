#ifndef WIP_D_COMM_PARENTINFO_H
#define WIP_D_COMM_PARENTINFO_H

#include "types.h"

// Knife::Comm::ParentInfo (0xd0 bytes): a wireless parent found by a scan. The vtable is data_0211b0a4. Fields are named
// by the functions below; the rest of the bss description is kept as bytes.
namespace Knife {
namespace Comm {

class ParentInfo {
public:
    BOOL isValid(void) const;
    u16 getMaxPlayers(void) const;
    u16 getCurrentPlayers(void) const;
    s32 getUserGameInfoSize(void) const;
    const void *getUserGameInfo(void) const;
    void cleanup(void);
    void decrementTTL(void);

    const void *vtbl;          // 0x00
    u16 checksum04;            // 0x04: compared with (infoLength40 + 0x41) / 2 by isValid
    u8 unk_06[0x40 - 0x06];
    u16 infoLength40;          // 0x40: length of the info block, 0x10 to 0x80 when valid
    u8 unk_42[2];
    u16 version44;             // 0x44: must be 1 when valid
    u8 unk_46[0x4e - 0x46];
    u8 userInfoLength;         // 0x4e: length of the info block (the user game info follows the 8-byte header)
    u8 unk_4f[0x54 - 0x4f];
    u32 magic;                 // 0x54: 'KNF' (0x464e4b) once the block is valid
    u16 maxPlayersM1;          // 0x58: maximum number of players minus one
    u16 currentPlayersM1;      // 0x5a: current number of players minus one
    u8 userGameInfo[0xc4 - 0x5c]; // 0x5c: user game info
    u8 emptyFlag;              // 0xc4: set by cleanup, cleared by a valid scan result
    u8 unk_c5[3];
    s32 field_c8;              // 0xc8
    s32 ttl;                   // 0xcc: time to live, decremented by decrementTTL
};

}
}

#endif
