#ifndef KNIFE_COMM_INTERRUPT_SECTION_H
#define KNIFE_COMM_INTERRUPT_SECTION_H

#include "knife/comm/wm_work.h"

namespace Knife {
namespace Comm {

class InterruptDisabledSection {
public:
    inline InterruptDisabledSection() : savedIme(WM_REG_IME) {
        WM_REG_IME = 0;
    }

    inline virtual ~InterruptDisabledSection() {
        (void)WM_REG_IME;
        WM_REG_IME = savedIme;
    }

private:
    u32 savedIme;
};

}
}

#endif
