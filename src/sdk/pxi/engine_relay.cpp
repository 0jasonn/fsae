#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/pxi/pxi_fifo.h"

// Tail call to PXI_Init (src/sdk/pxi/pxi_init.cpp). Every caller passes no arguments.
void Engine_Relay0201a070(void) {
    PXI_Init();
}
