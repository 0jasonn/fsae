#include "engine/functions.h"
#include "global.h"
#include "game/eff.h"

// eff_get_state() (0x0209b78c): the state word at data_0217c23c + 0xf50, cleared by the eff init functions
ARM s32 eff_get_state(void) {
    return *(s32 *)(data_0217c23c + 0xf50);
}
