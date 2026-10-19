#include "engine/functions.h"
#include "engine/common_d.h"
#include "engine/player.h"
#include "global.h"

ARM s32 fix_mul(s16 a, s16 b) {
    s32 p = a * b;
    s32 q = p >> 7;
    p += (u32)q >> 24;
    return (p << 8) >> 16;
}

ARM s16 fix_div(s32 a, s32 b) {
    if (b == 0) {
        return 0;
    }
    return _s32_div_f(a << 8, b);
}

ARM Entity *ObjPosCopy(Entity *src, Entity *dst) {
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
    dst->unk_50 = src->unk_50;
    dst->unk_52 = src->unk_52;
    return func_0208ae78(dst);
}

ARM void ObjPosCopy2(Entity *src, Entity *dst) {
    ObjPosCopy(src, dst);
    if (dst->unk_5e.b0 < 3) {
        dst->unk_5e.b0++;
    }
}

ARM void ObjPosCopyOfs32(Entity *src, Entity *dst, s32 dx, s32 dy) {
    dst->x.WORD = src->x.WORD + dx;
    dst->y.WORD = src->y.WORD + dy;
    dst->z = src->z;
    dst->unk_50 = src->unk_50;
    dst->unk_52 = src->unk_52;
    func_0208ae78(dst);
}

ARM void DropRupeeDir(s32 i, s32 value, s32 flags) {
    s32 idx;
    Entity *target;
    Entity *fx;
    void *a = KnifeApp_getInstance();
    target = data_0212ceb0[i].entity;
    if (data_0212c7d4[i] - value < 0) {
        if (KnifeApp_isWirelessMode(a) != 0) {
            return;
        }
        if (data_0212c7d4[i ^ 1] - value < 0) {
            return;
        }
        target = data_0212ceb0[i ^ 1].entity;
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
    fx = GetSetWork(0, idx, 1);
    if (fx == NULL) {
        return;
    }
    ObjPosCopy(data_0212ceb0[i].entity, fx);
    fx->direction = flags | 0x80;
    fx->zVelocity = 0x20000;
    fx->z.HALF.HI -= 4;
    AddRupee(target, (s16)(-value));
}
