#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/knife_sound.h"

// Knife::Sound::HandleFactory constructor (0x0208c188): builds the 16 sequence handles, then clears the used-slot mask
void func_0200c7b8(void *array, s32 count, u32 size, void *ctor, void *dtor);
extern "C" KnifeSoundSequenceHandle *Knife_Sound_SequenceHandle_ctor(KnifeSoundSequenceHandle *self);
extern "C" KnifeSoundSequenceHandle *Knife_Sound_SequenceHandle_dtor_SequenceHandle_08c45c(KnifeSoundSequenceHandle *self);
extern "C" KnifeSoundHandleFactory *Knife_Sound_HandleFactory_HandleFactory(KnifeSoundHandleFactory *self);
ARM KnifeSoundHandleFactory *Knife_Sound_HandleFactory_HandleFactory(KnifeSoundHandleFactory *self) {
    func_0200c7b8(self, 16, sizeof(KnifeSoundSequenceHandle), (void *)Knife_Sound_SequenceHandle_ctor,
                  (void *)Knife_Sound_SequenceHandle_dtor_SequenceHandle_08c45c);
    self->usedFlags = 0;
    return self;
}
