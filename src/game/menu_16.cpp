#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

// Forwarder to SndSys_StartActiveTimer (role not confirmed).
ARM void Menu_ForwardBf40c(s32 a, s32 b, s32 c, s32 d) {
    SndSys_StartActiveTimer(a, b, c, d);
}
