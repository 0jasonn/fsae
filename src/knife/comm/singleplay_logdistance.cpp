#include "engine/functions.h"
#include "global.h"
#include "knife/comm/knife_single_log.h"

// Knife::Single::SinglePlay::SinglePlayLogList::ResetDistance() (0x0209a598): the distance between the positions of the
// current and the oldest log entry (16.16 values divided by 16). The positions of an entry are the 32 bit words pos1 and
// pos2.

namespace Knife {
namespace Single {
namespace SinglePlay {

void SinglePlayLogList::ResetDistance(void) {
    VecFx32 currentPos = {0, 0, 0};
    currentPos.x = *(s32 *)&log[current].pos1 / 16;
    currentPos.y = *(s32 *)&log[current].pos2 / 16;
    VecFx32 oldestPos = {0, 0, 0};
    oldestPos.x = *(s32 *)&log[oldest].pos1 / 16;
    oldestPos.y = *(s32 *)&log[oldest].pos2 / 16;
    distance = VEC_Distance(&currentPos, &oldestPos);
}

}
}
}
