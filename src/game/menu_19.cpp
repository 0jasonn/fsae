#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

// Forwarder to ResChunk_OpenKNBA (role not confirmed). Plain linkage: the controller code calls it with two arguments.
extern "C" void Menu_ForwardC2cb4(s32 a, s32 b, s32 c, s32 d);
ARM void Menu_ForwardC2cb4(s32 a, s32 b, s32 c, s32 d) {
    ResChunk_OpenKNBA(a, b, c, d);
}
