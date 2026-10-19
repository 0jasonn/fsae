#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/objdecls.h"

// Link actor, first unit (module link). Address -> name:
//   0x02072704 link_init_072704 (original name link_init; the suffix keeps it apart from other link_init)
//   0x02072774 link_nop (no-op, provisional name)
//   0x02072778 link_stand, 0x02072798 link_walk, 0x020727b4 link_walk_init, 0x020727e0 link_walk_move (original names)
//   0x02072860 link_itemget, 0x0207287c itemget_init, 0x020728a8 itemget_move (original names)
//   0x020728fc itemget_nop (no-op, provisional name)
//   0x02072900 link_dead, 0x0207291c dead_init, 0x0207294c dead_move (original names)
//   0x020729d4 link_jitabata, 0x020729f0 jitabata_init (original names)
//   0x02072a1c link_setMode (tail call of func_02085934 with unk_1b)
//   0x02072a2c link_walkback, 0x02072a48 walkback_init, 0x02072a94 walkback_move (original names)
//   0x02072ae0 link_buttobi, 0x02072afc buttobi_init, 0x02072b38 buttobi_kurukuru, 0x02072bac buttobi_batari (original names)
//   0x02072bc8 link_standup, 0x02072be4 standup_init, 0x02072c24 standup_move_072c24 (original names)

extern u8 data_0212cebc[]; // indexed by e->type * 0x94
extern u8 data_0212ceb8[]; // u16 entries, indexed by e->type * 0x94
extern u8 data_0212cee8[]; // indexed by e->type * 0x94

void knife_event_check(Entity *e);

extern const EntityFunc link_walkSubActions[]; // indexed by e->subAction
extern const EntityFunc link_itemgetSubActions[]; // indexed by e->subAction
extern const EntityFunc link_deadSubActions[]; // indexed by e->subAction
extern const EntityFunc link_jitabataSubActions[]; // indexed by e->subAction
extern const EntityFunc link_walkbackSubActions[]; // indexed by e->subAction
extern const EntityFunc link_buttobiSubActions[]; // indexed by e->subAction
extern const EntityFunc link_standupSubActions[]; // indexed by e->subAction

ARM void link_init_072704(Entity *e) {
    e->action++;
    e->unk_1b = 0;
    if (data_0212cebc[e->type * 0x94] != 0) {
        knife_event_check(e);
    }
    e->unk_23 = 0xff;
    if (*(u16 *)&data_0212ceb8[e->type * 0x94] == 0) {
        *(u16 *)&data_0212ceb8[e->type * 0x94] = 0;
    }
}

ARM void link_nop(Entity *e) {
}

ARM void link_stand(Entity *e) {
    *(u16 *)&data_0212ceb8[e->type * 0x94] = 0;
}

ARM void link_walk(Entity *e) {
    link_walkSubActions[e->subAction](e);
}

ARM void link_walk_init(Entity *e) {
    e->subAction++;
    *(u16 *)&data_0212ceb8[e->type * 0x94] = 4;
}

ARM void link_walk_move(Entity *e) {
    u8 anim;

    if (e->timer != 0xff) {
        if (e->subtimer != 0) {
            e->subtimer--;
        } else {
            anim = e->animationState;
            e->speed = 0x100;
            e->direction = anim << 2;
            MoveDir(e);
            e->timer--;
            if (e->timer == 0) {
                data_0212cebc[e->type * 0x94] = 2;
            }
        }
    }
    func_02085934(e, e->unk_1b);
}

ARM void link_itemget(Entity *e) {
    link_itemgetSubActions[e->subAction](e);
}

ARM void itemget_init(Entity *e) {
    e->subAction++;
    *(u16 *)&data_0212ceb8[e->type * 0x94] = 0xad;
}

ARM void itemget_move(Entity *e) {
    if (e->timer != 0xff) {
        e->timer--;
        if (e->timer == 0) {
            data_0212cebc[e->type * 0x94] = 2;
        }
    }
    if (e->frame & 0x80) {
        return;
    }
    func_02085934(e, e->unk_1b);
}

ARM void itemget_nop(Entity *e) {
}

ARM void link_dead(Entity *e) {
    link_deadSubActions[e->subAction](e);
}

ARM void dead_init(Entity *e) {
    e->subAction++;
    *(u16 *)&data_0212ceb8[e->type * 0x94] = 0x1af;
}

ARM void dead_move(Entity *e) {
    if (data_0212cee8[e->type * 0x94] != 0) {
        if (!(e->frame & 0x80)) {
            do {
                UpdateAnimationSingleFrame(e);
            } while (!(e->frame & 0x80));
        }
        func_02085934(e, e->unk_1b);
        data_0212cee8[e->type * 0x94] = 0;
        return;
    }
    if (e->frame & 0x80) {
        return;
    }
    func_02085934(e, e->unk_1b);
}

ARM void link_jitabata(Entity *e) {
    link_jitabataSubActions[e->subAction](e);
}

ARM void jitabata_init(Entity *e) {
    e->subAction++;
    *(u16 *)&data_0212ceb8[e->type * 0x94] = 0x250;
}

ARM void link_setMode(Entity *e) {
    func_02085934(e, e->unk_1b);
}

ARM void link_walkback(Entity *e) {
    link_walkbackSubActions[e->subAction](e);
}

ARM void walkback_init(Entity *e) {
    e->subAction++;
    e->direction = ((e->animationState + 4) & 7) << 2;
    e->speed = 0x80;
    *(u16 *)&data_0212ceb8[e->type * 0x94] = 4;
}

ARM void walkback_move(Entity *e) {
    MoveDir(e);
    func_02085934(e, e->unk_1b);
    e->timer--;
    if (e->timer == 0) {
        data_0212cebc[e->type * 0x94] = 2;
    }
}

ARM void link_buttobi(Entity *e) {
    link_buttobiSubActions[e->subAction](e);
}

ARM void buttobi_init(Entity *e) {
    e->subAction++;
    *(u16 *)&data_0212ceb8[e->type * 0x94] = 0xae;
    e->direction = 9;
    e->speed = 0x400;
}

ARM void buttobi_kurukuru(Entity *e) {
    MoveDir(e);
    func_02085934(e, e->unk_1b);
    e->speed -= 0x14;
    if (e->x.HALF.HI <= 0xb8) {
        return;
    }
    e->x.HALF.HI = 0xb8;
    e->subAction++;
    *(u16 *)&data_0212ceb8[e->type * 0x94] = 0x1af;
    e->animationState = 2;
    SoundReq(0x1fc);
}

ARM void buttobi_batari(Entity *e) {
    if (e->frame & 0x80) {
        return;
    }
    func_02085934(e, e->unk_1b);
}

ARM void link_standup(Entity *e) {
    link_standupSubActions[e->subAction](e);
}

ARM void standup_init(Entity *e) {
    e->subAction++;
    e->zVelocity = 0x20000;
    *(u16 *)&data_0212ceb8[e->type * 0x94] = 0xc;
    SoundReq(0xd);
}

ARM void standup_move_072c24(Entity *e) {
    func_02085934(e, e->unk_1b);
    if (UpdateGravity(e, 0x4000) != 0) {
        return;
    }
    SoundReq(0xe);
    data_0212cebc[e->type * 0x94] = 2;
}
