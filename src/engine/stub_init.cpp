#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/stub_init_api.h"

// Empty entries at the start of the ARM9 code: the autoload callback and two no-op functions with dsd names.

void AutoloadCallback(void) {
}

void Stub_02004ee0(void) {
}

void Stub_02004ee4(void) {
}
