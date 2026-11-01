#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/engine_block_api.h"

// Returns the address of the work block at data_02129d54.
extern u8 data_02129d54[];

u8 *Engine_GetBlockD54(void) {
    return data_02129d54;
}
