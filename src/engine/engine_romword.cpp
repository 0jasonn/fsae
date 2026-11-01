#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/engine_romword_api.h"

// Returns the word at data_020dfb40 in the ROM data.
extern u32 data_020dfb40;

u32 Engine_ReadRomWord(void) {
    return data_020dfb40;
}
