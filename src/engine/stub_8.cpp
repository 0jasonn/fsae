#include "engine/functions.h"
#include "global.h"
#include "types.h"

void Stub_0200c8c4(void);

// Pass-through wrappers (dsd names Passthrough_0200c8f8, Passthrough_0200c90c): call the empty function and return the argument.
ARM int Passthrough_0200c8f8(int value) {
    Stub_0200c8c4();
    return value;
}

ARM int Passthrough_0200c90c(int value) {
    Passthrough_0200c8f8(value);
    return value;
}
