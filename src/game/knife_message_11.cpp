#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Unnamed stubs (owner not identified): empty slots or a single store, dsd names kept.

extern "C" void func_020a1100(void *self, u8 value);
extern "C" void func_020a1108(void *self, u8 value);

ARM void func_020a1100(void *self, u8 value) {
    *((u8 *)self + 0x77) = value;
}

ARM void func_020a1108(void *self, u8 value) {
    *((u8 *)self + 0x76) = value;
}

