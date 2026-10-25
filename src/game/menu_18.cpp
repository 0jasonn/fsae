#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

// Forwarder to SndRangeTree_Remove (role not confirmed). Plain linkage: the sound record code calls it with one argument
// (src/engine/sndtable_3.cpp), this definition passes all four argument registers on.
extern "C" void Menu_ForwardC28b0(s32 a, s32 b, s32 c, s32 d);
ARM void Menu_ForwardC28b0(s32 a, s32 b, s32 c, s32 d) {
    SndRangeTree_Remove(a, b, c, d);
}
