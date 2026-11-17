#include "engine/functions.h"

typedef struct SselTobiraCursorList {
    u32 cursor[3]; // cursor index of the stage select at which each door stays, indexed by type2
} SselTobiraCursorList;
extern const SselTobiraCursorList sselTobiraCursorList; // 0x020dae2c

// ssel_tobira_move, 0x0206f354. Counts the timer up and shows the door after 11 frames; the door is removed as soon
// as the stage select cursor (KnifeApp byte 0xcb0) leaves the stage it belongs to.
void ssel_tobira_move(Entity *e) {
    SselTobiraCursorList list = sselTobiraCursorList;
    e->unk_1b = 0xb4;
    e->spriteSettings.b16 = 0;
    e->timer++;
    if (e->timer >= 0xc) {
        e->spriteSettings.b0 = 1;
    }
    UpdateAnimationSingleFrame(e);
    if (list.cursor[e->type2] != ((u8 *)KnifeApp_getInstance())[0xcb0]) {
        PutObjWork(e);
    }
}
