#include "engine/functions.h"
#include "global.h"
#include "game/knife_single_log.h"

// Knife::Single::SinglePlay::SinglePlayLogList getters, 0x0209a31c to 0x0209a3c4 (SetLog 0x0209a084..0x0209a31c is not written yet).

namespace Knife {
namespace Single {
namespace SinglePlay {

// SinglePlayLogList::GetCurrentLog() const (0x0a31c)
ARM const SinglePlayLog *SinglePlayLogList::GetCurrentLog(void) const {
    return &log[current];
}

// SinglePlayLogList::GetCurrentLogPos() const (0x0a330)
ARM POS SinglePlayLogList::GetCurrentLogPos(void) const {
    return GetPosToInsert(current);
}

// SinglePlayLogList::GetNextLogPos() const (0x0a358): the position after the current entry, or the current one
// when the list holds a single entry.
ARM POS SinglePlayLogList::GetNextLogPos(void) const {
    u8 index = current;

    if (oldest != current) {
        index = (current + 1) % 128;
    }
    return GetPosToInsert(index);
}

// SinglePlayLogList::GetPrevLogPos() const (0x0a39c)
ARM POS SinglePlayLogList::GetPrevLogPos(void) const {
    return GetPosToInsert(unk_02[1]);
}

// SinglePlayLogList::GetPosToInsert(unsigned char) const (0x0a3c4): the position at index, moved by the average
// of the distance sums of the entries after it.
ARM POS SinglePlayLogList::GetPosToInsert(u8 index) const {
    POS pos;
    u8 i;
    s32 sumA = this->sumA;
    s32 sumB = this->sumB;

    pos.x = *(s16 *)((u8 *)this + index * 0x18 + 0xa);
    pos.y = *(s16 *)((u8 *)this + index * 0x18 + 0xe);
    if (oldest != index) {
        i = (index + 1) % 128;
        for (;;) {
            sumA += *(s32 *)((u8 *)this + i * 0x18 + 0x14);
            sumB += *(s32 *)((u8 *)this + i * 0x18 + 0x18);
            if (i == oldest) {
                break;
            }
            i = (i + 1) % 128;
        }
    }
    pos.x += sumA / 256;
    pos.y += sumB / 256;
    return pos;
}

}
}
}
