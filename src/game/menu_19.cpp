#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

// Forwarder to func_020c2c78 (role not confirmed). Plain linkage: the controller code calls it with two arguments.
extern "C" void Menu_ForwardC2cb4(s32 a, s32 b, s32 c, s32 d);
ARM void Menu_ForwardC2cb4(s32 a, s32 b, s32 c, s32 d) {
    func_020c2c78(a, b, c, d);
}
