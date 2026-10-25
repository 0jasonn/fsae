#include "engine/functions.h"
#include "global.h"

// Functions in this file (names invented, the debug build has none; the role of data_0217da60 is not known yet):
//   Knife_Message_setPendingPtr (setter), Knife_Message_getPendingPtr (getter)

extern void *data_0217da60; // one pointer, set by the setter and read by the getter

// Stores the pointer in data_0217da60 (0x020a3778, name invented)
extern "C" void Knife_Message_setPendingPtr(void *p);
ARM void Knife_Message_setPendingPtr(void *p) {
    data_0217da60 = p;
}

// Returns data_0217da60 (0x020a3788, name invented)
extern "C" void *Knife_Message_getPendingPtr(void);
ARM void *Knife_Message_getPendingPtr(void) {
    return data_0217da60;
}
