#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" void *Obj_DeletePassthrough(void *self);

void operator delete(void *block);
int Passthrough_0200c8f8(int value);

// Obj_DeletePassthrough(self) (0x0200c920): passes self through the stub at 0x0200c8f8, deletes it and returns it.
ARM void *Obj_DeletePassthrough(void *self) {
    Passthrough_0200c8f8((int)self);
    operator delete(self);
    return self;
}
