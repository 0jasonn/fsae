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

ARM Entity *CopyPosition(Entity *src, Entity *dst) {
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
    dst->unk_50 = src->unk_50;
    dst->unk_52 = src->unk_52;
    return func_0208ae78(dst);
}

ARM void func_02050354(Entity *src, Entity *dst) {
    CopyPosition(src, dst);
    if (dst->unk_5e.b0 < 3) {
        dst->unk_5e.b0++;
    }
}

ARM void PositionRelative(Entity *src, Entity *dst, s32 dx, s32 dy) {
    dst->x.WORD = src->x.WORD + dx;
    dst->y.WORD = src->y.WORD + dy;
    dst->z = src->z;
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
    fx = CreateFx(0, idx, 1);
    if (fx == NULL) {
        return;
    }
    CopyPosition(data_0212ceb0[i].unk_28, fx);
    fx->direction = flags | 0x80;
    fx->zVelocity = 0x20000;
    fx->z.HALF.HI -= 4;
    func_020260c8(target, (s16)(-value));
}
