#include "Unknown/D/Common_D.h"
#include "Unknown/Player.h"
#include "global.h"

ARM s32 func_020502e0(s16 a, s16 b) {
    s32 p = a * b;
    s32 q = p >> 7;
    p += (u32)q >> 24;
    return (p << 8) >> 16;
}

ARM s16 func_020502f8(s32 a, s32 b) {
    if (b == 0) {
        return 0;
    }
    return func_0200d948(a << 8, b);
}

ARM Entity *func_0205031c(Entity *src, Entity *dst) {
    dst->unk_30 = src->unk_30;
    dst->unk_34 = src->unk_34;
    dst->unk_38 = src->unk_38;
    dst->unk_50 = src->unk_50;
    dst->unk_52 = src->unk_52;
    return func_0208ae78(dst);
}

ARM void func_02050354(Entity *src, Entity *dst) {
    func_0205031c(src, dst);
    if (dst->unk_5e.b0 < 3) {
        dst->unk_5e.b0++;
    }
}

ARM void func_02050390(Entity *src, Entity *dst, s32 dx, s32 dy) {
    dst->unk_30.WORD = src->unk_30.WORD + dx;
    dst->unk_34.WORD = src->unk_34.WORD + dy;
    dst->unk_38 = src->unk_38;
    dst->unk_50 = src->unk_50;
    dst->unk_52 = src->unk_52;
    func_0208ae78(dst);
}

ARM void func_020503d0(s32 i, s32 value, s32 flags) {
    s32 idx;
    Entity *target;
    Entity *fx;
    void *a = func_0208da4c();
    target = data_0212ceb0[i].unk_28;
    if (data_0212c7d4[i] - value < 0) {
        if (func_0208de54(a) != 0) {
            return;
        }
        if (data_0212c7d4[i ^ 1] - value < 0) {
            return;
        }
        target = data_0212ceb0[i ^ 1].unk_28;
    }
    switch (value) {
        case 1:
            idx = 1;
            break;
        case 5:
            idx = 2;
            break;
        case 0x14:
            idx = 3;
            break;
        case 0x32:
            idx = 6;
            break;
        case 0x64:
            idx = 8;
            break;
        case 0xc8:
            idx = 9;
            break;
        default:
            return;
    }
    fx = func_02076858(0, idx, 1);
    if (fx == NULL) {
        return;
    }
    func_0205031c(data_0212ceb0[i].unk_28, fx);
    fx->unk_2b = flags | 0x80;
    fx->unk_10 = 0x20000;
    fx->unk_38.HALF.HI -= 4;
    func_020260c8(target, (s16)(-value));
}
