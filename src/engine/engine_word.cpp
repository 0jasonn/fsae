#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Returns the word stored at data_02128920 (name not known yet).
extern u32 data_02128920;

extern "C" u32 Engine_ReadWordA(void);

ARM u32 Engine_ReadWordA(void) {
    return data_02128920;
}
