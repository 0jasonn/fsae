#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" u32 Obj_GetField38(void *obj);

// Returns the word at +0x38 of the object.
ARM u32 Obj_GetField38(void *obj) {
    return *(u32 *)((u8 *)obj + 0x38);
}
