#include "engine/functions.h"
#include "global.h"
#include "actor/object/set66.h"
#include "actor/object/door_silver.h"
#include "engine/irq.h"

extern DoorSilverBlock displayState;

// set68_type2 (0x0207583c): follows its parent. Action 0 sets up the sprite (a type2 other than 0 also takes the
// second palette setup and display registers), action 1 waits for bit 0 of the game flags, action 2 shows or hides the
// actor by the key state and removes it when bit 1 of the game flags is set.
void set68_type2(Entity *e) {
    switch (e->action) {
        case 0:
            e->action = 1;
            e->spriteSettings.b0 = 1;
            if (e->type2 == 0) {
                e->spriteSettings.b14 = 0;
            } else {
                e->spriteSettings.b14 = 2;
                e->unk_5e.b0 = 3;
                *(u32 *)&e->spriteSettings = (*(u32 *)&e->spriteSettings & ~0xc00) | 0x400;
                displayState.unk_66 = 0xf40;
                displayState.unk_68 = 0x809;
            }
            InitAnimationForceUpdate(e, e->type2);
            break;
        case 1:
            if (!(em12_typeMasks[0] & 1)) {
                break;
            }
            if (e->type2 == 0) {
                SoundReq(0x21c);
            }
            e->action++;
            break;
        case 2:
            e->spriteSettings.b0 = (frameState.frameCount & 4) == 0;
            if (em12_typeMasks[0] & 2) {
                PutObjWork(e);
            }
            break;
    }
    e->x.WORD = e->parent->x.WORD;
    e->y.WORD = e->parent->y.WORD;
    e->z.WORD = e->parent->z.WORD;
    UpdateAnimationSingleFrame(e);
}
