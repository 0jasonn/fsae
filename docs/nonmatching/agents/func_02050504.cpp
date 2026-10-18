// Nonmatching: value/20, rem%20 and rem/5 are computed by mwcc as one shared divide; original does them separately (about 60 lines differ, register allocation).
#include "Unknown/D/Common_D.hpp"
#include "Unknown/Player.hpp"
#include "global.h"

ARM extern "C" void func_02050504(s32 i, s32 value) {
    s16 k;
    u16 rem;
    s16 n20;
    s16 n5;
    s16 n1;
    n20 = value / 20;
    rem = value - 20 * (value / 20);
    k = n20 - 1;
    if (n20 != 0) {
        do {
            func_020503d0(i, 20, func_0208455c() & 0x1f);
        } while (k-- != 0);
    }
    n5 = rem / 5;
    k = n5 - 1;
    if (n5 != 0) {
        do {
            func_020503d0(i, 5, func_0208455c() & 0x1f);
        } while (k-- != 0);
    }
    n1 = rem % 5;
    k = n1 - 1;
    if (n1 != 0) {
        do {
            func_020503d0(i, 1, func_0208455c() & 0x1f);
        } while (k-- != 0);
    }
}
