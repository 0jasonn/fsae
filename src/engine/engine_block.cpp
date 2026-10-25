#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Returns the address of the work block at data_02129d54.
extern u8 data_02129d54[];

extern "C" u8 *Engine_GetBlockD54(void);

ARM u8 *Engine_GetBlockD54(void) {
    return data_02129d54;
}
