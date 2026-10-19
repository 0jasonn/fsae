#include "engine/functions.h"
#include "global.h"
#include "object/bomb.h"

// Bomb actor (module bomb). Original names from the debug build.
//   bomb_move, bomb_lift, bomb_throw_init, bomb_clearThrowFlag, bomb_setThrowFlag4, bomb_throw_end, bomb_delete,
//   bomb_end

// Clears the timer and sets subtimer 1 once the bomb is no longer carried, then runs the shared object update.
ARM void bomb_move(Entity *e) {
    if (VARS(BombVars, e)->carrierLink != 0) {
        e->timer = 0;
        e->subtimer = 1;
    }
    func_02085ccc(e);
}

// Lifted: forgets the carrier and runs the handler for the current subaction.
ARM void bomb_lift(Entity *e) {
    VARS(BombVars, e)->carrierLink = 0;
    bomb_liftTable[e->subAction](e);
}

// Throw start: advances the subaction; on the first frame (timer and subtimer both 0) sets the bomb's flying state and
// spawns its child object, then runs the shared update with the template of type2.
ARM void bomb_throw_init(Entity *e) {
    Entity *tmpl;
    Entity *child;

    tmpl = OBJ_TEMPLATE(e->type2);
    e->subAction++;
    if (e->timer == 0 && e->subtimer == 0) {
        e->timer = 0xf0;
        e->unk_40 = 0x16;
        e->attackDamage = 0xa;
        e->attackKnockback = 0xc;
        e->statusFlags = 8;
        e->hitbox = bomb_hitbox;
        e->poseId = 0xb;
        e->unk_20 = 0xce;
        e->spriteSettings.b0 = 1;
        e->spriteSettings.b6 = 3;
        e->spriteSettings.b20 = 1;
        e->spriteSettings.b16 = e->spriteSettings.b20;
        e->unk_1b = 9;
        e->unk_1a = 0;
        InitAnimationForceUpdate(e, 5);
        child = GetObjWork();
        if (child != NULL) {
            child->parent = e;
            child->objId = 4;
            child->objKind = 8;
            *(u16 *)child->unk_64 = 1;
            child->type = 0xff;
            RegistObjWork(2, child);
        }
    }
    func_0208ab14(e, tmpl);
}

// Clears the throw flag (unk_2e), set when the bomb is not thrown.
ARM void bomb_clearThrowFlag(Entity *e) {
    e->unk_2e = 0;
}

// Sets the throw flag (unk_2e) to 4 when the throw starts.
ARM void bomb_setThrowFlag4(Entity *e) {
    e->unk_2e = 4;
}

// End of a throw: steps the action back, resets the subaction and caps the timer at 0x3c.
ARM void bomb_throw_end(Entity *e) {
    e->action--;
    e->subAction = 0;
    if (e->timer > 0x3c) {
        e->timer = 0x3c;
    }
}

// Removes the bomb from the object list.
ARM void bomb_delete(Entity *e) {
    PutObjWork(e);
}

// Counts the timer down; the bomb is removed when it runs out.
ARM void bomb_end(Entity *e) {
    if (e->timer-- == 0) {
        PutObjWork(e);
    }
}
