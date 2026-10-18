// Nonmatching: 2 extra lines around the flag store (cmp not reused by the original).
// Nonmatching: remaining diff is one extra "cmp r2,#4" before the final conditional store (original reuses flags).
#include "Unknown/Entity.hpp"
#include "Unknown/Player.hpp"
#include "global.h"

ARM extern "C" u8 func_02050280(Entity *e) {
    u8 v = e->unk_2b;
    u8 cur = e->unk_2a;
    int t;
    u32 w;
    if (!(v & 0x80)) {
        t = (v & 0x1c) >> 2;
        if (t & 1) {
            if (((t - cur + 1) & 4) == 0) {
                return cur;
            }
        }
        cur = (v >> 2) & 0x7e;
        w = *(u32 *)&e->unk_1c;
        if (cur <= 4) {
            w &= ~4;
            *(u32 *)&e->unk_1c = w;
        } else {
            w |= 4;
        }
        e->unk_2a = cur;
        if (cur > 4) {
            *(u32 *)&e->unk_1c = w;
        }
    }
    return cur;
}
