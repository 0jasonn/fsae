#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/obj_get38_api.h"

// Returns the word at +0x38 of the object.
u32 Obj_GetField38(void *obj) {
    return *(u32 *)((u8 *)obj + 0x38);
}
