#include "engine/functions.h"
#include "knife/comm/comm_parentinfo.h"

namespace Knife {
namespace Comm {

// ParentInfo::getUserGameInfoSize() const (0x02090810): the info length less the 8-byte header when the 'KNF' magic is
// present, the whole length otherwise
s32 ParentInfo::getUserGameInfoSize(void) const {
    if (userInfoLength >= 8) {
        if (magic == 0x464e4b) {
            return userInfoLength - 8;
        }
    }
    return userInfoLength;
}

}
}
