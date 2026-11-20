#include "engine/functions.h"
#include "knife/comm/singleplay_init.h"
#include "global.h"
#include "knife/comm/singleplay.h"

// Knife::Single::SinglePlay destructor (0x02070dbc). It resets the single play state through
// Knife_Single_SinglePlay_Initialize (0x02093bbc) and returns the object. Written as a plain function taking self.
void *Knife_Single_SinglePlay_dtor_SinglePlay(void *self) {
    Knife_Single_SinglePlay_Initialize();
    return self;
}
