#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Empty entries at the start of the ARM9 code: the autoload callback and two no-op functions with dsd names.
extern "C" void AutoloadCallback(void);

ARM void AutoloadCallback(void) {
}

ARM void Stub_02004ee0(void) {
}

ARM void Stub_02004ee4(void) {
}
