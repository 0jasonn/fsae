#include "knife/comm/interrupt_section.h"

namespace Knife {
namespace Comm {

const void *WirelessManager::getSharedData(int index) const {
    InterruptDisabledSection section;
    const s32 state = this->state;

    if (state != 8 && state != 11) {
        return 0;
    }

    u32 slot = slots[index];
    if (slot == 0) {
        return 0;
    }

    return reinterpret_cast<const void *>(slot + 4);
}

u32 WirelessManager::getReceivedAIDs() const {
    InterruptDisabledSection section;
    const s32 state = this->state;

    if (state != 8 && state != 11) {
        return 0;
    }

    return linkValue;
}

}
}
