#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/comm_parentinfo.h"

// Knife::Comm::ParentInfo::getUserGameInfo (0x0209083c)

namespace Knife {
namespace Comm {

// ParentInfo::getUserGameInfo() const (0x0209083c): the user game info block (after the header when the magic is present)
ARM const void *ParentInfo::getUserGameInfo(void) const {
    if (userInfoLength >= 8) {
        if (magic == 0x464e4b) {
            return userGameInfo;
        }
    }
    return (const void *)&magic;
}

}
}
