#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Empty function (dsd name Stub_0200c8c4): returns at once.
ARM void Stub_0200c8c4(void) {
}

// Passes its argument through the empty function (dsd name Passthrough_0200c8c8): calls Stub_0200c8c4, returns the argument.
ARM int Passthrough_0200c8c8(int value) {
    Stub_0200c8c4();
    return value;
}
