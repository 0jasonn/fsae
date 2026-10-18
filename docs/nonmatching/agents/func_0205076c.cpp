// Nonmatching: 10 lines differ, locals best/bestDist/i are in swapped registers (best should be r6, bestDist r4).
#include "Unknown/D/Common_D.hpp"
#include "Unknown/Player.hpp"
#include "global.h"

extern "C" {
s32 func_02085a88(Entity *a, Entity *b, s32 c, s32 d);
}

ARM extern "C" u8 func_0205076c(Entity *a, s32 b, s32 c) {
    u8 best = 0xff;
    u8 i;
    u16 bestDist = 0xffff;
    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        if (func_02085a88(a, data_0212ceb0[i].unk_28, b, c) != 0) {
            Entity *other = data_0212ceb0[i].unk_28;
            s16 ay = a->unk_34.HALF.HI;
            s16 oy = other->unk_34.HALF.HI;
            s16 ox = other->unk_30.HALF.HI;
            s16 ax = a->unk_30.HALF.HI;
            s32 dy = oy - ay;
            s32 dx = ox - ax;
            u16 dist = (s16)(-(s16)dy) + (s16)(-(s16)dx);
            if (bestDist > dist) {
                bestDist = dist;
                best = i;
            }
        }
    }
    return best;
}
