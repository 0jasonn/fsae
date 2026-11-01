#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/sound/knifesound_dtor_api.h"

// Knife::Sound::Handle destructor (0x0208bed0): frees the handle record and returns it
void *Knife_Sound_Handle_dtor_Handle(void *self) {
    operator delete(self);
    return self;
}
