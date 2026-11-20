#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/fatfs/engine_romword_api.h"


u32 Engine_ReadRomWord(void) {
    return data_020dfb40;
}
