#include "engine/functions.h"
#include "global.h"

// Set5d actor, fall and standup units (module set5d). Address -> name:
//   0x0205fd34 set5d_fall (original name, state table set5d_fall_states indexed by e->subAction)
//   0x0205fd50 fall_init (original name)
//   0x0205fdf0 fall_fade (original name)
//   0x0205fe24 fall_move (original name)
//   0x0205feb0 fall_anim (updates the animation of the falling entity)
//   0x0205febc set5d_standup (original name, state table set5d_standup_states indexed by e->subAction)
//   0x0205fed8 set5d_standup_init (advances subAction and sets the target word)
//   0x0205fef4 set5d_standup_move (original name)

void ObjSetTargetWord(Entity *e, u16 value); // defined in src/game/npc.cpp, not yet in functions.h

typedef struct Vars_Set5d {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ Entity *linked;
} Vars_Set5d;

extern const EntityFunc set5d_fall_states[]; // fall state table indexed by e->subAction
extern const EntityFunc set5d_standup_states[]; // standup state table indexed by e->subAction
extern u32 em12_typeMasks[]; // 0x02134954: bit 0 of word 0 is set when the fall ends (also used by em12 as type masks)

ARM void set5d_fall(Entity *e) {
    set5d_fall_states[e->subAction](e);
}

ARM void fall_init(Entity *e) {
    s32 index;

    e->subAction++;
    e->z.HALF.HI = -0xa0;
    e->timer = 0x3c;
    ObjSetTargetWord(e, 8);
    index = 0x23;
    e->spriteSettings.b16 = GetObjColor(index);
    e->unk_5e.b2 = 3;
    e->spriteSettings.b14 = 1;
    GetSetWork(0x68, 2, 0)->parent = e;
    GetSetWork(0x68, 2, 4)->parent = e;
    SoundReq(0x248 - index);
}

ARM void fall_fade(Entity *e) {
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    e->subAction++;
    FadeSet(0, 2);
}

ARM void fall_move(Entity *e) {
    if (e->z.HALF.HI < 0) {
        e->z.WORD += 0x4000;
        UpdateAnimationSingleFrame(e);
        return;
    }
    em12_typeMasks[0] |= 1;
    e->spriteSettings.b16 = GetObjColor(0x10);
    e->unk_5e.b2 = 0;
    e->subAction++;
    SoundReq(0x216);
    ObjSetTargetWord(e, 0xa);
}

ARM void fall_anim(Entity *e) {
    UpdateAnimationSingleFrame(e);
}

ARM void set5d_standup(Entity *e) {
    set5d_standup_states[e->subAction](e);
}

ARM void set5d_standup_init(Entity *e) {
    e->subAction++;
    ObjSetTargetWord(e, 9);
}

ARM void set5d_standup_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    e->linkedEntity->unk_00[2] = 2;
    if (!(e->frame & 0x80)) {
        return;
    }
    e->linkedEntity->unk_00[4] = 1;
    e->unk_5e.b2 = 1;
}
