#include "engine/functions.h"
#include "engine/common_d.h"
#include "engine/player.h"
#include "global.h"

ARM s32 fix_mul(s16 lhs, s16 rhs) {
    s32 product = lhs * rhs;
    s32 shifted = product >> 7;
    product += (u32)shifted >> 24;
    return (product << 8) >> 16;
}

ARM s16 fix_div(s32 numerator, s32 denominator) {
    if (denominator == 0) {
        return 0;
    }
    return _s32_div_f(numerator << 8, denominator);
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

ARM void DropRupeeDir(s32 playerIndex, s32 value, s32 flags) {
    s32 idx;
    Entity *target;
    Entity *fx;
    void *knifeApp = KnifeApp_getInstance();
    target = data_0212ceb0[playerIndex].entity;
    if (data_0212c7d4[playerIndex] - value < 0) {
        if (KnifeApp_isWirelessMode(knifeApp) != 0) {
            return;
        }
        if (data_0212c7d4[playerIndex ^ 1] - value < 0) {
            return;
        }
        target = data_0212ceb0[playerIndex ^ 1].entity;
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
    ObjPosCopy(data_0212ceb0[playerIndex].entity, fx);
    fx->direction = flags | 0x80;
    fx->zVelocity = 0x20000;
    fx->z.HALF.HI -= 4;
    AddRupee(target, (s16)(-value));
}
