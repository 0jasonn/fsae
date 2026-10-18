// Nonmatching: flag bit (bit 2 of unk_1c) and unk_2a store order differ (about 13 lines); best attempt kept.
#include "Unknown/Player.hpp"
#include "global.h"

ARM extern "C" u8 func_02050200(Entity *e) {
    u8 v = data_0212ceb0[e->unk_0a].unk_0d[0];
    u8 t;
    if (v == 0xff) {
        return e->unk_2a;
    }
    t = (v & 0x1c) >> 2;
    if (t & 1) {
        if (((t + 1 - e->unk_2a) & 4) == 0) {
            return e->unk_2a;
        }
    }
    u8 r = t & 6;
    u32 f = (t > 4);
    u32 w = *(u32 *)&e->unk_1c;
    w = (w & ~4) | (f << 31 >> 29);
    *(u32 *)&e->unk_1c = w;
    e->unk_2a = r;
    return r;
}
