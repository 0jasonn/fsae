#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"
#include "actor/enemy/em1b.h"

extern const s8 em1b_dirDeltaTable[]; // em1b_dirDeltaTable, two entries (-1, +1)

extern u16 frameCounter;
void ofsset(Entity *e); // em1b_2 is not the unit that defines it, see the note in the report
extern EntityFunc em1b_type1Actions[];   // em1b_type1Actions, indexed by e->action
extern const u8 em1b_type1Hitbox[];      // em1b_type1Hitbox, used when type == 1
extern const u8 em1b_otherHitbox[];      // em1b_otherHitbox, used for the other types

// Type 1 movement: follows the trail stored in this entity by the parent (ofsset in the next unit), updates the animation.
void em1b_type1_move(Entity *e) {
    Vars_Em1bType1 *vars = VARS(Vars_Em1bType1, e);
    u8 slot;
    u8 trailByte;
    u32 shift;
    u8 nextAnim;
    s8 dx;
    s8 dy;

    vars->savedX = e->x.HALF.HI;
    vars->savedY = e->y.HALF.HI;
    slot = (frameCounter + 1) & 7;
    trailByte = vars->trail[slot];
    dx = (trailByte & 0xf) - 8;
    dy = ((trailByte & 0xf0) >> 4) - 8;
    e->x.HALF.HI += dx;
    e->y.HALF.HI += dy;
    shift = ((frameCounter + 1) & 7) << 2;
    nextAnim = ((vars->frameAnims >> shift) & 7) + (e->type << 3);
    if (nextAnim != e->animationState) {
        e->animationState = nextAnim;
        InitAnimationForceUpdate(e, nextAnim);
    }
    if (e->type != 3) {
        ofsset(e);
    }
    UpdateAnimationSingleFrame(e);
}
