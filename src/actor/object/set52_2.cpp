#include "engine/functions.h"
#include "global.h"
#include "actor/object/template.h"
#include "engine/player.h"

// Set52 actor, second unit (module set52). Address -> name:
//   0x02070658 set52_move, 0x02070718 set52_end (original names)
//   0x0207073c Set52 (main, provisional name: dispatches e->action through set52_actions)
//   set52_init (0x02070598) is in scratch/agentD/nonmatching/set52_init.cpp

extern const EntityFunc set52_actions[]; // indexed by e->action
extern u16 frameCounter;

void set52_move(Entity *e) {
    Entity *tmpl;

    tmpl = OBJ_TEMPLATE(e->type);
    func_0208ab14(e, tmpl);
    UpdateAnimationSingleFrame(e);
    if (data_0212ceb0[e->type].actionFlags != 0) {
        if ((frameCounter & 3) != 0) {
            return;
        }
        e->spriteSettings.b16 ^= 7;
        return;
    }
    if (e->frame & 0x80) {
        e->action++;
        InitAnimationForceUpdate(e, (e->animationState >> 1) + 8);
        return;
    }
    PutObjWork(e);
}

void set52_end(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        PutObjWork(e);
    }
}

void Set52(Entity *e) {
    set52_actions[e->action](e);
}
