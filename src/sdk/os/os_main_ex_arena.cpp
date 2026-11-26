#include "global.h"
#include "types.h"
#include "sdk/os/pair_block.h"

void OS_DisableMainExArena(void) {
    data_02129cac.flags = 0;
}
