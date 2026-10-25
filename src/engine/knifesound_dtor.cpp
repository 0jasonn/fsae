#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Knife::Sound::Handle destructor (0x0208bed0): frees the handle record and returns it
extern "C" void *Knife_Sound_Handle_dtor_Handle(void *self);
ARM void *Knife_Sound_Handle_dtor_Handle(void *self) {
    operator delete(self);
    return self;
}
