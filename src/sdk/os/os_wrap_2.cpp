#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/os_wrap_api.h"

// OSi_IrqDma0: runs the DMA 0 interrupt callback (OSi_IrqCallback(0)).
void OSi_IrqDma0(void) {
    OSi_IrqCallback(0);
}
