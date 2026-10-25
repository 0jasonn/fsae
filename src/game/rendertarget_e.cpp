#include "engine/functions.h"
#include "global.h"
#include "game/message_e.h"

// Functions in this file (original names from the debug build):
//   RenderTarget::getNumberOfUsingOBJ() const (0x020a4ee0)

extern "C" s32 func_020c61f4(s32 a, s32 b);
extern "C" void OS_Terminate(void);

namespace Knife {
namespace Message {

// RenderTarget::getNumberOfUsingOBJ() const (0x020a4ee0): the OBJ count of the target, for modes whose last digit is 4
// (anything else terminates the program)
ARM s32 RenderTarget::getNumberOfUsingOBJ(void) const {
    if (mode % 10 == 4) {
        return func_020c61f4(unk_38, unk_3c);
    }
    OS_Terminate();
    return 0;
}

}
}
