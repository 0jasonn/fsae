#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Knife::Sound base constructor (0x0208bcd4, 12 bytes with its literal; 0x0208bcd8 is inside it, not a function of its own):
// writes the base vtable (data_0211aad8) to the first word of the object
extern u8 data_0211aad8[];

extern "C" void func_0208bcd4(void *self);
ARM void func_0208bcd4(void *self) {
    *(void **)self = data_0211aad8;
}
