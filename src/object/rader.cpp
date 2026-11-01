#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"

// Rader (radar) parent and child actors (module rader). Address -> name:
//   0x0206305c Set10, 0x020630b0 raderParent (original names)

extern const EntityFunc data_02115a5c[]; // indexed by e->action (parent)
extern Entity *data_0212c838[]; // child entity per type2 (set while the child is active)

void raderChild(Entity *e);
void raderParent(Entity *e);

void Set10(Entity *e) {
    if (e->type == 0) {
        raderParent(e);
        return;
    }
    raderChild(e);
    data_0212c838[e->type2] = (e->spriteSettings.b0 != 0) ? e : NULL;
    e->spriteSettings.b0 = 0;
}

void raderParent(Entity *e) {
    data_02115a5c[e->action](e);
}

// Rader parent, third unit (module rader). Address -> name:
//   0x020630cc rp_init (original name)

extern u8 localPlayerIndex; // player index that is shown as the wireless partner

void rp_init(Entity *e) {
    Entity *child;
    s32 k;
    void *knife;
    s32 spawned;
    s32 i;

    for (k = 0; k < 4; k++) {
        *(u32 *)((u8 *)&data_0212c7c8 + k * 4 + 0x70) = 0;
    }
    spawned = 0;
    knife = KnifeApp_getInstance();
    for (i = 0; i < data_0212c7c8.playerCount; i++) {
        if (!(i == localPlayerIndex && KnifeApp_isWirelessMode(knife))) {
            child = GetSetWork(0x10, 1, (u8)i);
            if (child != NULL) {
                child->parent = e;
                child->child = data_0212ceb0[i].entity;
                child->subtimer = spawned;
                spawned++;
            }
        }
    }
    e->action++;
}
