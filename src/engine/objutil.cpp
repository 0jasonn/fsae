#include "engine/functions.h"
#include "engine/objutil.h"
#include "engine/objutil_5.h"
#include "engine/player.h"
#include "global.h"

// TODO(headers): this declaration of data_0212c7d4 differs from the shared one; see the header restructure report.
extern s32 data_0212c7d4[];

// 0x02050280 (original name ObjCdirSet, plain symbol). Maps the low bits of e->direction to the animation state,
// moving the b2 sprite bit with it. Returns the new animation state.
u32 ObjCdirSet(Entity *e) {
    u8 dir = e->direction;
    u32 cur = e->animationState;
    u32 word;
    u32 type;

    if (!(dir & 0x80)) {
        type = (dir & 0x1c) >> 2;
        if (type & 1) {
            if (((type - cur + 1) & 4) == 0) {
                return cur;
            }
        }
        cur = (dir >> 2) & 0x7e;
        word = *(u32 *)&e->spriteSettings;
        e->animationState = cur;
        if (cur <= 4) {
            word &= ~4;
            *(u32 *)&e->spriteSettings = word;
        } else {
            word |= 4;
            *(u32 *)&e->spriteSettings = word;
        }
    }
    return cur;
}

s32 fix_mul(s16 lhs, s16 rhs) {
    s32 product = lhs * rhs;
    s32 shifted = product >> 7;
    product += (u32)shifted >> 24;
    return (product << 8) >> 16;
}

s16 fix_div(s32 numerator, s32 denominator) {
    if (denominator == 0) {
        return 0;
    }
    return _s32_div_f(numerator << 8, denominator);
}

Entity *ObjPosCopy(Entity *src, Entity *dst) {
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
    dst->layer = src->layer;
    dst->areaIndex = src->areaIndex;
    return func_0208ae78(dst);
}

void ObjPosCopy2(Entity *src, Entity *dst) {
    ObjPosCopy(src, dst);
    if (dst->unk_5e.b0 < 3) {
        dst->unk_5e.b0++;
    }
}

void ObjPosCopyOfs32(Entity *src, Entity *dst, s32 dx, s32 dy) {
    dst->x.WORD = src->x.WORD + dx;
    dst->y.WORD = src->y.WORD + dy;
    dst->z = src->z;
    dst->layer = src->layer;
    dst->areaIndex = src->areaIndex;
    func_0208ae78(dst);
}

void DropRupeeDir(u8 playerIndex, u16 value, u8 flags) {
    s32 idx;
    Entity *target;
    Entity *fx;
    void *knifeApp = KnifeApp_getInstance();
    target = playerWork[playerIndex].entity;
    if (data_0212c7d4[playerIndex] - value < 0) {
        if (KnifeApp_isWirelessMode(knifeApp) != 0) {
            return;
        }
        if (data_0212c7d4[playerIndex ^ 1] - value < 0) {
            return;
        }
        target = playerWork[playerIndex ^ 1].entity;
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
    ObjPosCopy(playerWork[playerIndex].entity, fx);
    fx->direction = flags | 0x80;
    fx->zVelocity = 0x20000;
    fx->z.HALF.HI -= 4;
    AddRupee(target, (s16)(-value));
}
