#include "engine/functions.h"
#include "global.h"

extern "C" {
extern u8 *data_021848b0; // sound state pointer
}

// func_020c05dc: returns the current sound state pointer.
extern "C" u8 *func_020c05dc(void);
ARM u8 *func_020c05dc(void) {
    return data_021848b0;
}
