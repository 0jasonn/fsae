#include "knife/comm/interrupt_section.h"

namespace Knife {
namespace Comm {

u32 WirelessManager::getSharedDataSize() const {
    InterruptDisabledSection section;
    const s32 state = this->state;

    if (state != 8 && state != 11) {
        return 0;
    }

    return static_cast<u32>(timer2) - 4;
}

}
}
