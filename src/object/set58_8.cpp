#include "engine/functions.h"
#include "global.h"
#include "object/set58.h"

// Set58 milkcrown, sazanami, hikari and tamahikari actors (module set58, unit 8). Address -> name:
//   0x02073bbc set58_milkcrown (original name; dispatches on e->action)
//   0x02073bd8 milkcrown_init (original name)
//   0x02073c1c milkcrown_move (original name)
//   0x02073c40 set58_sazanami (original name; dispatches on e->action)
//   0x02073c5c sazanami_init (original name)
//   0x02073c88 sazanami_move (original name)
//   0x02073cb0 set58_hikari (original name; dispatches on e->action)
//   0x02073ccc hikari_init (original name)
//   0x02073d3c hikari_move (original name)
//   0x02073da8 set58_tamahikari (original name; dispatches on e->action)
//   0x02073dc4 tamahikari_init (original name)
//   0x02073df4 tamahikari_move (original name)

extern const EntityFunc set58_milkcrownActions[];  // set58_milkcrownActions, indexed by e->action
extern const EntityFunc set58_sazanamiActions[];   // set58_sazanamiActions, indexed by e->action
extern const EntityFunc set58_hikariActions[];     // set58_hikariActions, indexed by e->action
extern const EntityFunc set58_tamahikariActions[]; // set58_tamahikariActions, indexed by e->action

ARM void set58_milkcrown(Entity *e) {
    set58_milkcrownActions[e->action](e);
}

ARM void milkcrown_init(Entity *e) {
    set58_actionInit(e);
    e->spriteSettings.b0 = 1;
    e->z.HALF.HI = 0;
    e->unk_5e.b0 = 1;
    SoundReq(0x213);
}

ARM void milkcrown_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        PutObjWork(e);
    }
}

ARM void set58_sazanami(Entity *e) {
    set58_sazanamiActions[e->action](e);
}

ARM void sazanami_init(Entity *e) {
    set58_actionInit(e);
    e->spriteSettings.b0 = 1;
    e->unk_5e.b0 = 0;
}

ARM void sazanami_move(Entity *e) {
    if (em12_typeMasks & 2) {
        PutObjWork(e);
    } else {
        UpdateAnimationSingleFrame(e);
    }
}

ARM void set58_hikari(Entity *e) {
    set58_hikariActions[e->action](e);
}

ARM void hikari_init(Entity *e) {
    set58_actionInit(e);
    e->timer = 0x78;
    e->spriteSettings.b0 = 1;
    e->unk_5e.b0 = 1;
    if (func_02081b64() != 0) {
        e->spriteSettings.b16 = e->spriteSettings.b16 + 1;
    }
    SoundReq(0x212);
}

ARM void hikari_move(Entity *e) {
    Entity *child;

    UpdateAnimationSingleFrame(e);
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    child = GetSetWork(0x58, 3, 0);
    if (child == NULL) {
        return;
    }
    ObjPosCopyOfs32(e, child, 0, -0x80000);
    em12_typeMasks |= 2;
    PutObjWork(e);
}

ARM void set58_tamahikari(Entity *e) {
    set58_tamahikariActions[e->action](e);
}

ARM void tamahikari_init(Entity *e) {
    set58_actionInit(e);
    e->spriteSettings.b0 = 1;
    e->unk_5e.b0 = 1;
}

ARM void tamahikari_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        PutObjWork(e);
    }
}
