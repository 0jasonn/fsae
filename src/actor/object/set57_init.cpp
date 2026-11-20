#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "actor/object/set57.h"

// set57_init (0x020731f0): sets the palette from set57_paletteIndex; in game mode 2 the object is nudged by (4, -2)
// and shown. Registers the BG cell under it (idx from the grid position) with the tile id of its type.
void set57_init(Entity *e) {
    u16 *base;
    u16 index;
    e->action = 1;
    e->unk_5e.b0 = 0;
    e->spriteSettings.b16 = set57_paletteIndex[e->type];
    if (gameState.unk_01 == 2) {
        e->spriteSettings.b0 = 1;
        e->x.HALF.HI += 4;
        e->y.HALF.HI -= 2;
    }
    InitAnimationForceUpdate(e, 0);
    e->unk_28 = (Random() & 0xf0) + 1;
    base = (u16 *)GetBgBuffAdrs(e->layer);
    index = ((e->x.HALF.HI - mapState.originX) >> 4) | (((e->y.HALF.HI - mapState.originY) >> 4) << 6);
    V57(e)->cellPtr = base + 2 + index;
    V57(e)->tileIndex = set57_tileIds[e->type];
    func_0208366c(V57(e)->tileIndex, index, e->layer);
}
