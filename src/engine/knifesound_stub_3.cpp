#include "engine/functions.h"
#include "global.h"

// Knife::Sound leaf slot functions (the one-instruction bodies of the Handle and Archive classes). They take the object
// as self; the vtable pointer is written by the constructors, which are not in this unit.
//   0x0208bcd8 knifeSoundSetVtbl, 0x0208bce4 knifeSoundNop0, 0x0208bcfc knifeSoundNop1,
//   0x0208bd00 Knife_Sound_Archive_apply, 0x0208bd24 knifeSoundForwardHandle, 0x0208bdec knifeSoundClearWord,
//   0x0208bdf8 knifeSoundSetWordReturnOne, 0x0208becc knifeSoundNop2, 0x0208bee4 knifeSoundNop3,
//   0x0208bee8 knifeSoundReturnZero, 0x0208bef0 knifeSoundGetFlag0e

// 0x0208bdec: clears the word at the start of the object
extern "C" void knifeSoundClearWord(void *self);
ARM void knifeSoundClearWord(void *self) {
    *(u32 *)self = 0;
}

// 0x0208bdf8: stores the word argument at the start of the object and returns 1
extern "C" int knifeSoundSetWordReturnOne(void *self, u32 value);
ARM int knifeSoundSetWordReturnOne(void *self, u32 value) {
    *(u32 *)self = value;
    return 1;
}
