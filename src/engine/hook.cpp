#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Calls the function pointer at data_020dfaa0 (dsd names Forward_0200c550 and CallHook_0200c55c).
extern void (*data_020dfaa0)(void);
void CallHook_0200c55c(void);

void Forward_0200c550(void) {
    CallHook_0200c55c();
}

void CallHook_0200c55c(void) {
    data_020dfaa0();
}
