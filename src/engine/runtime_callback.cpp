#include "types.h"

extern "C" void (*data_021277b0)(void *, void *, s32);
extern void Stub_02008138(void);

// The callers pass three arguments and discard the result. Parameter types are provisional.
extern "C" void func_02008110(void *a, void *b, s32 c) {
    if (data_021277b0 != NULL) {
        data_021277b0(a, b, c);
    } else {
        Stub_02008138();
    }
}
