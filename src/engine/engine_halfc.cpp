#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Returns the halfword at data_02129c70.
extern u16 data_02129c70;

extern "C" u16 Engine_ReadHalfC(void);

ARM u16 Engine_ReadHalfC(void) {
    return data_02129c70;
}
