#include "engine/functions.h"
#include "global.h"
#include "object/set38.h"

// IroyukaEffectSet, 0x0206bbf4 (unmangled in the original, so C linkage).
// Places the effect object made by GetSetWork(0x39) at the cell packed in the 0x94-byte table entry for e->type.
extern u8 data_0212ced2[];

ARM extern "C" void IroyukaEffectSet(Entity *e) {
    Entity *effect;
    s32 cell;

    effect = GetSetWork(0x39, 0, 0);
    if (effect == NULL) {
        return;
    }
    cell = ((u32)*(u16 *)(data_0212ced2 + e->type * 0x94) << 15) >> 16;
    effect->x.HALF.HI = ((cell & 0x3f) << 4) | 8;
    effect->y.HALF.HI = ((cell & 0xfc0) >> 2) | 8;
    effect->layer = e->layer;
}
