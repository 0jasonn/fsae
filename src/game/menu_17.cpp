#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

// Forwarder to SndVoice_Release (role not confirmed).
ARM void Menu_ForwardBfd1c(s32 a, s32 b, s32 c, s32 d) {
    SndVoice_Release(a, b, c, d);
}
