#include "engine/functions.h"
#include "global.h"

// Knife::Sound leaf slot functions (the one-instruction bodies of the Handle and Archive classes). They take the object
// as self; the vtable pointer is written by the constructors, which are not in this unit.
//   0x0208bcd8 knifeSoundSetVtbl, 0x0208bce4 knifeSoundNop0, 0x0208bcfc knifeSoundNop1,
//   0x0208bd00 Knife_Sound_Archive_apply, 0x0208bd24 knifeSoundForwardHandle, 0x0208bdec knifeSoundClearWord,
//   0x0208bdf8 knifeSoundSetWordReturnOne, 0x0208becc knifeSoundNop2, 0x0208bee4 knifeSoundNop3,
//   0x0208bee8 knifeSoundReturnZero, 0x0208bef0 knifeSoundGetFlag0e

extern "C" void knifeSoundNop1(void *self);
ARM void knifeSoundNop1(void *self) {
}

// 0x0208bd00: applies the archive's random seed when the field at +4 is not already the one returned by func_020c05dc
extern "C" void *func_020c05dc(void *self);
extern "C" void CRYPTOi__r_rand_set_default_init_flag(void *p);
extern "C" void Knife_Sound_Archive_apply(void *self);
ARM void Knife_Sound_Archive_apply(void *self) {
    if (func_020c05dc(self) == (void *)((u8 *)self + 4)) {
        return;
    }
    CRYPTOi__r_rand_set_default_init_flag((void *)((u8 *)self + 4));
}

// 0x0208bd24: passes the first word of the second argument to func_020c1660 (tail call)
extern "C" void func_020c1660(void *p);
extern "C" void knifeSoundForwardHandle(void *unused, void **handle);
ARM void knifeSoundForwardHandle(void *unused, void **handle) {
    func_020c1660(*handle);
}
