#include "engine/functions.h"
#include "game/opdemo_c.h"
#include "global.h"

// Four-byte mask table (rodata at data_020d813c), indexed by the mask index of PlCheckMochiage.
typedef struct MochiageMask {
    u8 bits[4];
} MochiageMask;
extern const MochiageMask data_020d813c;

// PlCheckMochiage (0x0205501c): returns FALSE when one of the two players stands in a lift-up position over the other.
extern "C" int PlCheckMochiage(Entity *a, Entity *b);

ARM int PlCheckMochiage(Entity *a, Entity *b) {
    MochiageMask masks = data_020d813c;
    Entity *pair[2];
    u8 index;
    s32 i;

    pair[0] = a;
    pair[1] = b;
    index = (u8)(a->animationState >> 1);
    i = 0;
    do {
        Entity *target = pair[i];
        u32 hit = (u32)func_02083d18(target, 0, 3);
        do {
            int value;
            u8 bits;
            s32 xBit;
            s32 yBit;
            if (hit == 0) {
                break;
            }
            value = hit;
            if (hit == 0x1e) {
                value = 10;
            } else if (hit == 0x1f) {
                value = 5;
            } else if (hit >= 0xf) {
                break;
            }
            xBit = (target->x.HALF.HI >> 3) & 1;
            yBit = ((target->y.HALF.HI + 3) >> 3) & 1;
            bits = (u8)((xBit ^ 1) + 1 << ((yBit ^ 1) << 1));
            switch (index) {
                    case 0:
                        bits |= (u8)((bits & 3) << 2);
                        break;
                    case 1:
                        bits |= (u8)((bits & 0xa) >> 1);
                        break;
                    case 2:
                        bits |= (u8)((bits & 0xc) >> 2);
                        break;
                    case 3:
                        bits |= (u8)((bits & 5) << 1);
                        break;
                    default:
                        break;
                }
                if ((masks.bits[index] & (value & bits)) != 0) {
                return 0;
            }
        } while (0);
        i++;
        index = (u8)(index ^ 2);
    } while (i < 2);
    return 1;
}
