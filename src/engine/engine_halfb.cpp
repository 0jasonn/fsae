#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/engine_halfb_api.h"

// Returns the halfword at data_02129c60.
extern u16 data_02129c60;

u16 Engine_ReadHalfB(void) {
    return data_02129c60;
}
