#include "engine/functions.h"
#include "global.h"
#include "knife/comm/knife_single_log.h"

// Knife::Single::SinglePlay::SinglePlayLogList::SetLog, 0x0209a084 and 0x0209a2e0 (both overloads are plain extern "C"
// functions named by their symbols.txt names, object pointer first). The POS arguments are 16.16 values stored as
// one 32 bit word each (the entity x and y at +0x30 and +0x34). Header names: current (+0) is the cursor, oldest (+1)
// is the newest index written by SetLog, unk_02[1] (+3) the previous cursor, unk_02[0] (+2) the entry count.

namespace Knife {
namespace Single {
namespace SinglePlay {

// SetLog(POS const&, POS const&, unsigned short, long, short, short, short) (0x0209a084) is parked in
// scratch/agentA/nonmatching/Knife_Single_SinglePlay_SinglePlayLogList_SetLog_09a084.cpp.
extern "C" int Knife_Single_SinglePlay_SinglePlayLogList_SetLog_09a084(SinglePlayLogList *self, const POS &a, const POS &b, u16 kind, s32 c, s16 threshold, s16 sumAddA, s16 sumAddB);

// SetLog(OBJ_WORK_ const*, unsigned short, long, short, short, short) (0x0209a2e0): takes the position from the object
extern "C" int Knife_Single_SinglePlay_SinglePlayLogList_SetLog_09a2e0(SinglePlayLogList *self, const Entity *obj, u16 kind, s32 c, s16 threshold, s16 sumAddA, s16 sumAddB);
int Knife_Single_SinglePlay_SinglePlayLogList_SetLog_09a2e0(SinglePlayLogList *self, const Entity *obj, u16 kind, s32 c, s16 threshold, s16 sumAddA, s16 sumAddB) {
    return Knife_Single_SinglePlay_SinglePlayLogList_SetLog_09a084(self, *(const POS *)&obj->x, *(const POS *)&obj->y, kind, c, threshold, sumAddA, sumAddB);
}

}
}
}

// Knife::Single::SinglePlay::SinglePlayLogList getters, 0x0209a31c to 0x0209a3c4 (SetLog 0x0209a084..0x0209a31c is not written yet).

namespace Knife {
namespace Single {
namespace SinglePlay {

// SinglePlayLogList::GetCurrentLog() const (0x0a31c)
const SinglePlayLog *SinglePlayLogList::GetCurrentLog(void) const {
    return &log[current];
}

// SinglePlayLogList::GetCurrentLogPos() const (0x0a330)
POS SinglePlayLogList::GetCurrentLogPos(void) const {
    return GetPosToInsert(current);
}

// SinglePlayLogList::GetNextLogPos() const (0x0a358): the position after the current entry, or the current one
// when the list holds a single entry.
POS SinglePlayLogList::GetNextLogPos(void) const {
    u8 index = current;

    if (oldest != current) {
        index = (current + 1) % 128;
    }
    return GetPosToInsert(index);
}

// SinglePlayLogList::GetPrevLogPos() const (0x0a39c)
POS SinglePlayLogList::GetPrevLogPos(void) const {
    return GetPosToInsert(unk_02[1]);
}

// SinglePlayLogList::GetPosToInsert(unsigned char) const (0x0a3c4): the position at index, moved by the average
// of the distance sums of the entries after it.
POS SinglePlayLogList::GetPosToInsert(u8 index) const {
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
