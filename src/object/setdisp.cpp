#include "engine/functions.h"
#include "global.h"

// EffectSet (0x02076a20): spawns a child work of kind 0xf and links it to e as its parent. Returns the child, or NULL.
extern "C" Entity *EffectSet(Entity *e, int kind, int arg);
ARM Entity *EffectSet(Entity *e, int kind, int arg) {
    Entity *child;

    child = GetSetWork(0xf, kind, arg);
    if (child != NULL) {
        ObjPosCopy(e, child);
        child->parent = e;
    }
    return child;
}

// SetDisp (0x02076a50): spawns a display work (kind 0x60) placed at e, copying its timer, layer and sprite settings.
ARM Entity *SetDisp(Entity *e, u8 a, u8 b, u8 c) {
    Entity *child;

    child = GetSetWork(0x60, a, b);
    if (child == NULL) {
        return NULL;
    }
    ObjPosCopy(e, child);
    child->timer = c;
    child->unk_1b = e->unk_1b;
    child->spriteSettings.b20 = e->spriteSettings.b16;
    child->spriteSettings.b16 = child->spriteSettings.b20;
    child->spriteSettings.b14 = e->spriteSettings.b14;
    child->spriteSettings.b30 = e->spriteSettings.b30;
    child->spriteSettings.b6 = e->spriteSettings.b6;
    child->unk_20 = e->unk_20;
    child->unk_5e.b0 = 0;
    return child;
}
