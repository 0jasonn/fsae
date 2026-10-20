#include "engine/functions.h"
#include "game/stageseldecls.h"

// Tama0a actor family, first unit. Address -> name (original names from symbols.txt):
//   0x0207c974 Tama0a, 0x0207c9a8 tama0a_init, 0x0207ca34 tama0a_move, 0x0207cb1c Tama0b

extern const EntityFunc data_020dc9ec[]; // Tama0a action table, indexed by e->action
extern const EntityFunc data_020dca78[]; // Tama0b action table for type != 0
extern const EntityFunc data_020dca60[]; // Tama0b action table for type 0

// Tama0a, 0x0207c974. Runs the action while the parent is alive (its health byte is nonzero), otherwise removes it.
ARM void Tama0a(Entity *e) {
    if (e->parent->health != 0) {
        data_020dc9ec[e->action](e);
    } else {
        PutObjWork(e);
    }
}

// tama0a_init, 0x0207c9a8. Copies the parent's sprite settings and position, then starts the first action.
ARM void tama0a_init(Entity *e) {
    Entity *parent = e->parent;
    e->action = 1;
    e->spriteSettings.b0 = 1;
    e->unk_5e.b0 = 3;
    e->spriteSettings.b30 = parent->spriteSettings.b30;
    e->spriteSettings.b14 = parent->spriteSettings.b14;
    ObjPosCopyOfs32(parent, e, 0, 1);
    InitAnimationForceUpdate(e, 0);
    EnqueueSFX(0x9c);
}

// tama0a_move, 0x0207ca34. Follows the parent, runs the animation and, when the frame bit 0 is set on a type 0
// actor, spawns or moves the matching child. Removes the actor when frame bit 7 is set.
ARM void tama0a_move(Entity *e) {
    Entity *other;
    ObjPosCopyOfs32(e->parent, e, 0, 1);
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 1) != 0 && e->type == 0) {
        u8 kind = e->type2;
        e->frame = 0;
        if (kind == 0) {
            other = GetTamaWork(0xb);
            if (other != 0) {
                ObjPosCopy(e, other);
            }
        } else {
            other = GetTamaWork(0x11);
            if (other != 0) {
                Entity *aim;
                ObjPosCopy(e, other);
                other->parent = e->parent;
                other->y.HALF.HI -= 0x1a;
                other->type = 1;
                other->type2 = 1;
                aim = EmGetAimPl();
                other->direction = GetFacingDirection(e, aim);
                other->timer = aim->type;
                EnqueueSFX(0xb5);
            }
        }
    }
    if ((e->frame & 0x80) != 0) {
        PutObjWork(e);
    }
}

// Tama0b, 0x0207cb1c. Runs the action of the table for its type.
ARM void Tama0b(Entity *e) {
    if (e->type != 0) {
        data_020dca78[e->action](e);
    } else {
        data_020dca60[e->action](e);
    }
}
