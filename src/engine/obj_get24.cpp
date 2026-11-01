#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/obj_get24_api.h"

// Returns the word at +0x24 of the object.
u32 Obj_GetField24(void *obj) {
    return *(u32 *)((u8 *)obj + 0x24);
}
