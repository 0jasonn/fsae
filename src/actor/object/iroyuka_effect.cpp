#include "engine/functions.h"
#include "global.h"
#include "actor/object/set38.h"
#include "engine/player.h"

// IroyukaEffectSet, 0x0206bbf4 (unmangled in the original, so C linkage).
// Places the effect object made by GetSetWork(0x39) at the cell packed in PlayerData.unk_22 of the slot for e->type.

extern "C" void IroyukaEffectSet(Entity *e) {
    Entity *effect;
    s32 cell;

    effect = GetSetWork(0x39, 0, 0);
    if (effect == NULL) {
        return;
    }
    cell = ((u32)playerWork[e->type].unk_22 << 15) >> 16;
    effect->x.HALF.HI = ((cell & 0x3f) << 4) | 8;
    effect->y.HALF.HI = ((cell & 0xfc0) >> 2) | 8;
    effect->layer = e->layer;
}
