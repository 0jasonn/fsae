#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" void *Obj_DeleteAfterStub(void *self);

void Stub_0200c8c4(void);
int Passthrough_0200c8f8(int value);
void operator delete(void *block);

// Obj_DeleteAfterStub(self) (0x0200c8dc): runs the empty stub, deletes self and returns it.
ARM void *Obj_DeleteAfterStub(void *self) {
    Stub_0200c8c4();
    operator delete(self);
    return self;
}
