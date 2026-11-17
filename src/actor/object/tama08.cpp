#include "engine/functions.h"
#include "actor/object/tama08.h"

// Tama08 family, address -> name (original names from symbols.txt):
//   0x0207f84c Tama08, 0x0207f874 tama08_normal, 0x0207f890 tama08_damage,
//   0x0207f8e0 tama08_init, 0x0207f960 tama08_wait

// Tama08, 0x0207f84c. Runs the state table entry that func_02085294 picks.
void Tama08(Entity *e) {
    data_020dcf74[func_02085294()](e);
}

// tama08_normal, 0x0207f874. Runs the action of the current state.
void tama08_normal(Entity *e) {
    data_020dcf60[e->action](e);
}

// tama08_damage, 0x0207f890. A contact with exactly 0x80 removes the actor; otherwise it is bounced: action 4, the
// direction flipped by 0x10 and the speed and the z velocity set.
void tama08_damage(Entity *e) {
    if (e->contactFlags == 0x80) {
        PutObjWork(e);
        return;
    }
    e->action = 4;
    e->direction = e->direction ^ 0x10;
    e->speed = 0x80;
    e->zVelocity = 0x12000;
    e->statusFlags = 0;
    InitAnimationForceUpdate(e, 8);
}

// Sets the initial state, animation and hitbox from the actor's direction.
void tama08_init(Entity *e) {
    u32 spriteWord;

    e->action = 1;
    e->timer = 8;
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b4 = 1;
    spriteWord = *(u32 *)&e->spriteSettings;
    if ((e->direction & 0x8) != 0) {
        if ((e->direction & 0x10) == 0) {
            spriteWord = spriteWord | 4;
            *(u32 *)&e->spriteSettings = spriteWord;
        }
        e->animationState = 1;
        e->hitbox = data_020dcf50;
    } else {
        if ((e->direction & 0x10) != 0) {
            spriteWord = spriteWord | 8;
            *(u32 *)&e->spriteSettings = spriteWord;
        }
        e->animationState = 2;
        e->hitbox = data_020dcf58;
    }
    InitAnimationForceUpdate(e, e->animationState);
}

// Detaches after the timer expires. Removes the actor if its parent has picked a different child.
void tama08_wait(Entity *e) {
    Entity *parent = e->parent;

    if (parent != NULL && parent->child != e) {
        PutObjWork(e);
        return;
    }
    e->timer = e->timer - 1;
    if (e->timer != 0) {
        return;
    }
    e->action = 2;
    e->statusFlags = e->statusFlags | 0x80;
    e->layer = e->layer & 0xcfff;
    func_0208ae78(e);
    if (e->parent != NULL) {
        e->parent->child = NULL;
    }
}
