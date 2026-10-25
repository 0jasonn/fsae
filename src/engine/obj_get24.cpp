#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" u32 Obj_GetField24(void *obj);

// Returns the word at +0x24 of the object.
ARM u32 Obj_GetField24(void *obj) {
    return *(u32 *)((u8 *)obj + 0x24);
}
