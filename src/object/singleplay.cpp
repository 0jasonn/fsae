#include "engine/functions.h"
#include "global.h"

// Knife::Single::SinglePlay destructor (0x02070dbc). It resets the single play state through
// Knife_Single_SinglePlay_Initialize (0x02093bbc) and returns the object. Written as a plain function taking self.
void Knife_Single_SinglePlay_Initialize(void); // C++ name _Z34Knife_Single_SinglePlay_Initializev
extern "C" void *Knife_Single_SinglePlay_dtor_SinglePlay(void *self);
ARM void *Knife_Single_SinglePlay_dtor_SinglePlay(void *self) {
    Knife_Single_SinglePlay_Initialize();
    return self;
}
