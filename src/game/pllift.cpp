#include "engine/functions.h"
#include "engine/player.h"
#include "engine/frame_counter.h"

// Fields of a lift entity past the common block.
typedef struct LiftVars {
    u8 unk_00[0x6c];
    Entity *anchor; // 0x6c: object whose child is the carried player entity
} LiftVars;

extern const s8 *const data_0211525c[];

// PlLiftSync(OBJ_WORK_*) (0x02054ddc): while the player entity carried by a lift is in its action 2, copies the lift's
// height, priority and layer to it and offsets its position by the per-frame table of the lift.
void PlLiftSync(Entity *lift) {
    u8 frame = lift->frame & 0x7f;
    Entity *carried = VARS(LiftVars, lift)->anchor->child;
    u8 pose = carried->unk_1a >> 4;
    const s8 *offsets = data_0211525c[pose];

    if (carried->action != 2) {
        return;
    }
    carried->z.WORD = lift->z.WORD;
    carried->spriteSettings.b30 = lift->spriteSettings.b30;
    carried->layer = lift->layer;
    if (lift->spriteSettings.flipX) {
        carried->x.HALF.HI = lift->x.HALF.HI - offsets[frame];
    } else {
        carried->x.HALF.HI = lift->x.HALF.HI + offsets[frame];
    }
    carried->z.HALF.HI += offsets[frame + 1];
    carried->y.WORD = lift->y.WORD + 1;
    if (playerWork[lift->type].specialState == 4) {
        carried->spriteSettings.b14 = lift->spriteSettings.b14;
        ObjLiftPrioCheck(carried);
        if ((carried->unk_1a & 0xf) != 2) {
            return;
        }
        switch (frameCounter.frame & 3) {
        case 1:
            carried->x.HALF.HI++;
            break;
        case 3:
            carried->x.HALF.HI--;
            break;
        }
    } else if (lift->animationState >> 1 != 0) {
        carried->y.WORD = lift->y.WORD + 1;
    } else {
        carried->y.WORD = lift->y.WORD - 1;
    }
}
