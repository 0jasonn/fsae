#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/engine_halfc_api.h"

// Returns the halfword at data_02129c70.
extern u16 data_02129c70;

u16 Engine_ReadHalfC(void) {
    return data_02129c70;
}
