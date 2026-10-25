#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/comm_parentinfo.h"

// Knife::Comm::ParentInfo getters, 0x020907a0 to 0x02090810 (isValid, 0x02090708, is parked)

namespace Knife {
namespace Comm {

// ParentInfo::getMaxPlayers() const (0x020907a0): the stored value plus one, 0 when the info is not valid
ARM u16 ParentInfo::getMaxPlayers(void) const {
    if (userInfoLength >= 8) {
        if (isValid()) {
            return maxPlayersM1 + 1;
        }
    }
    return 0;
}

// ParentInfo::getCurrentPlayers() const (0x020907d8): the stored value plus one, 0 unless the magic is present
ARM u16 ParentInfo::getCurrentPlayers(void) const {
    if (userInfoLength >= 8) {
        if (magic == 0x464e4b) {
            return currentPlayersM1 + 1;
        }
    }
    return 0;
}

}
}
