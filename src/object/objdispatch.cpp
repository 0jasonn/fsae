#include "engine/functions.h"
#include "global.h"
#include "object/objdispatch.h"

// Generic object dispatch, 0x02076b24. Runs the entry of data_02116588 for the object's id, then clears the contact
// flag bit 0x80 that the update has just used.
ARM void objDispatchClearContact(Entity *e) {
    data_02116588[e->objId](e);
    e->contactFlags = e->contactFlags & 0x7f;
}
