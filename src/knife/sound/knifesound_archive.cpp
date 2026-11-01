#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/sound/knifesound_archive.h"

// Knife::Sound leaf and archive destructor (0x0208bce4 .. 0x0208bcfc).
//   0x0208bce4 knifeSoundNop0, 0x0208bce8 Knife_Sound_Archive_dtor_Archive

// Empty slot: a bare return
void knifeSoundNop0(void *self) {
}

// Archive destructor (deleting form): frees the block and returns it
void *Knife_Sound_Archive_dtor_Archive(void *self) {
    operator delete(self);
    return self;
}
