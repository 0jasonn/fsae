#include "engine/functions.h"
#include "global.h"
#include "game/knife_single_log.h"

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
ARM int Knife_Single_SinglePlay_SinglePlayLogList_SetLog_09a2e0(SinglePlayLogList *self, const Entity *obj, u16 kind, s32 c, s16 threshold, s16 sumAddA, s16 sumAddB) {
    return Knife_Single_SinglePlay_SinglePlayLogList_SetLog_09a084(self, *(const POS *)&obj->x, *(const POS *)&obj->y, kind, c, threshold, sumAddA, sumAddB);
}

}
}
}
