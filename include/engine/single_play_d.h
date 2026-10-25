#ifndef WIP_D_SINGLE_PLAY_D_H
#define WIP_D_SINGLE_PLAY_D_H

#include "types.h"

// Knife::Single::SinglePlay state (the object the controller, formation and warp functions work on). Offsets from the
// start of the object. Only the fields the D functions read or write are named.
namespace Knife {
namespace Single {
namespace SinglePlay {

class SinglePlayLogList {
public:
    void Initialize(void); // 0x0209a060, C++ member (mangled name in symbols.txt)
};

}
}
}

typedef struct SinglePlayWork {
    u8 contNo;               // 0x00: the controlling player (0 or 1)
    u8 contChanging;         // 0x01: nonzero while a controller change is in progress
    u8 formationChanging;    // 0x02
    u8 reqKind;              // 0x03: pending request (1: controller change, 2: formation change)
    u8 reqNo;                // 0x04: pending request number (0xff: none)
    u8 unk_05[2];
    u8 flags07;              // 0x07: bit 0 controller changed, bit 1 controller sound pending, bit 2 formation pending
    u8 unk_08;
    u8 unk_09;
    u8 unk_0a;
    u8 unk_0b;
    u8 unk_0c;
    u8 unk_0d[2];
    u8 unk_0f;
    u8 unk_10[2];
    u8 unk_12;               // 0x12
    u8 unk_13[0x1a - 0x13];
    u16 unk_1a;              // 0x1a: key mask set by SetContNoDirect
    u8 unk_1c[0x20 - 0x1c];
    u16 unk_20;              // 0x20: set to 0xffff by the initializers
    u16 unk_22;
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
    u8 unk_2a[0x2c - 0x2a];
    u16 unk_2c;
    u16 unk_2e;
    void *unk_30;            // 0x30
    u8 unk_34[0x34];         // 0x34: the log list (SinglePlayLogList, Initialize at 0x0209a060)
} SinglePlayWork;

#endif
