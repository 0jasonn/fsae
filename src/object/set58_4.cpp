#include "engine/functions.h"
#include "global.h"
#include "object/objdecls.h"
#include "object/set58.h"

// Set58 hane open, hamon and youseidama actions (module set58). Address -> name:
//   0x0207382c hane_open (original name)
//   0x02073890 set58_nop (provisional name, empty action)
//   0x02073894 set58_hamon (provisional name; dispatches on e->action)
//   0x020738b0 hamon_init (original name)
//   0x020738dc set58_hamonUpdate (provisional name), 0x020738e8 set58_youseidama (provisional)
//   0x02073904 youseidama_init is in scratch/agentD/nonmatching (near miss)

extern KnifeObjAffineSrcData scrollArgs;     // scrollArgs
extern const EntityFunc set58_hamonActions[]; // set58_hamonActions, indexed by e->action
extern const EntityFunc set58_youseidamaActions[]; // set58_youseidamaActions, indexed by e->action

ARM void hane_open(Entity *e) {
    s32 speed;

    speed = e->speed - 0x20;
    e->speed = speed;
    if (speed == 0x100) {
        e->action = 2;
        func_02085d34(e);
        em12_typeMasks |= 0x20;
        return;
    }
    scrollArgs.data[0] = speed;
    scrollArgs.data[1] = 0x100;
    scrollArgs.data[2] = 0;
    ObjAffineSet2(&scrollArgs, e);
}

ARM void set58_nop(Entity *e) {
}

ARM void set58_hamon(Entity *e) {
    set58_hamonActions[e->action](e);
}

ARM void hamon_init(Entity *e) {
    set58_actionInit(e);
    e->spriteSettings.b0 = 1;
    e->unk_5e.b0 = 0;
}

ARM void set58_hamonUpdate(Entity *e) {
    UpdateAnimationSingleFrame(e);
}

ARM void set58_youseidama(Entity *e) {
    set58_youseidamaActions[e->action](e);
}
