#ifndef KNIFE_COMM_KNIFE_SINGLE_LOG_H
#define KNIFE_COMM_KNIFE_SINGLE_LOG_H

#include "engine/functions.h"
#include "sdk/fx/fx.h"

// Position pair entry used by the single player log (4 bytes, passed and returned by value).
typedef struct POS {
    s16 x;
    s16 y;
} POS;

namespace Knife {
namespace Single {
namespace SinglePlay {

// One log entry, 0x18 bytes. Field names are provisional.
class SinglePlayLog {
public:
    void Initialize(void);
    void SetPos(const POS &a, const POS &b, u16 kind, s32 c, s32 d, s32 e);
    int CheckEqualPos(const POS &a, const POS &b) const;

    u16 kind;   // 0x00
    u8 unk_02[2];
    POS pos1;   // 0x04
    POS pos2;   // 0x08
    s32 c;      // 0x0c
    s32 d;      // 0x10
    s32 e;      // 0x14
};

// Log list of the single player (0xc10 bytes). Entries start at +4 and are indexed with a 0x18 stride;
// the byte at +0 is the current index and +1 the oldest index. Field names are provisional.
class SinglePlayLogList {
public:
    void Initialize(void);
    const SinglePlayLog *GetCurrentLog(void) const;
    POS GetCurrentLogPos(void) const;
    POS GetNextLogPos(void) const;
    POS GetPrevLogPos(void) const;
    POS GetPosToInsert(u8 index) const;
    void ResetDistance(void);
    void UpdateCurrentLogDistance(s16 distance);

    u8 current;  // 0x00
    u8 oldest;   // 0x01
    u8 unk_02[2]; // unk_02[1] at 0x03 is the previous index
    SinglePlayLog log[128]; // 0x04
    s32 distance; // 0xc04
    s32 sumA;     // 0xc08
    s32 sumB;     // 0xc0c
};

}
}
}

#endif
