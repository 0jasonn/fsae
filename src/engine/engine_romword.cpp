#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Returns the word at data_020dfb40 in the ROM data.
extern u32 data_020dfb40;

extern "C" u32 Engine_ReadRomWord(void);

ARM u32 Engine_ReadRomWord(void) {
    return data_020dfb40;
}
