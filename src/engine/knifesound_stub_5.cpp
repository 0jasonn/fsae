#include "engine/functions.h"
#include "global.h"

// Knife::Sound leaf slot functions (the one-instruction bodies of the Handle and Archive classes). They take the object
// as self; the vtable pointer is written by the constructors, which are not in this unit.
//   0x0208bcd8 knifeSoundSetVtbl, 0x0208bce4 knifeSoundNop0, 0x0208bcfc knifeSoundNop1,
//   0x0208bd00 Knife_Sound_Archive_apply, 0x0208bd24 knifeSoundForwardHandle, 0x0208bdec knifeSoundClearWord,
//   0x0208bdf8 knifeSoundSetWordReturnOne, 0x0208becc knifeSoundNop2, 0x0208bee4 knifeSoundNop3,
//   0x0208bee8 knifeSoundReturnZero, 0x0208bef0 knifeSoundGetFlag0e

extern "C" void knifeSoundNop3(void *self);
ARM void knifeSoundNop3(void *self) {
}

// 0x0208bee8: slot that reports 0
extern "C" int knifeSoundReturnZero(void *self);
ARM int knifeSoundReturnZero(void *self) {
    return 0;
}

// 0x0208bef0: returns the byte at +0x0e (the sound slot's player index)
extern "C" u8 knifeSoundGetFlag0e(void *self);
ARM u8 knifeSoundGetFlag0e(void *self) {
    return ((u8 *)self)[0x0e];
}
