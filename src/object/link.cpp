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

void knife_event_check(Entity *e);

extern const EntityFunc link_walkSubActions[]; // indexed by e->subAction
extern const EntityFunc link_itemgetSubActions[]; // indexed by e->subAction
extern const EntityFunc link_deadSubActions[]; // indexed by e->subAction
extern const EntityFunc link_jitabataSubActions[]; // indexed by e->subAction
extern const EntityFunc link_walkbackSubActions[]; // indexed by e->subAction
extern const EntityFunc link_buttobiSubActions[]; // indexed by e->subAction
extern const EntityFunc link_standupSubActions[]; // indexed by e->subAction

void link_init_072704(Entity *e) {
    e->action++;
    e->unk_1b = 0;
    if (data_0212ceb0[e->type].state != 0) {
        knife_event_check(e);
    }
    e->unk_23 = 0xff;
    if (data_0212ceb0[e->type].unk_08 == 0) {
        data_0212ceb0[e->type].unk_08 = 0;
    }
}

void link_nop(Entity *e) {
}

void link_stand(Entity *e) {
    data_0212ceb0[e->type].unk_08 = 0;
}

void link_walk(Entity *e) {
    link_walkSubActions[e->subAction](e);
}

void link_walk_init(Entity *e) {
    e->subAction++;
    data_0212ceb0[e->type].unk_08 = 4;
}

void link_walk_move(Entity *e) {
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
                data_0212ceb0[e->type].state = 2;
            }
        }
    }
    func_02085934(e, e->unk_1b);
}

void link_itemget(Entity *e) {
    link_itemgetSubActions[e->subAction](e);
}

void itemget_init(Entity *e) {
    e->subAction++;
    data_0212ceb0[e->type].unk_08 = 0xad;
}

void itemget_move(Entity *e) {
    if (e->timer != 0xff) {
        e->timer--;
        if (e->timer == 0) {
            data_0212ceb0[e->type].state = 2;
        }
    }
    if (e->frame & 0x80) {
        return;
    }
    func_02085934(e, e->unk_1b);
}

void itemget_nop(Entity *e) {
}

void link_dead(Entity *e) {
    link_deadSubActions[e->subAction](e);
}

void dead_init(Entity *e) {
    e->subAction++;
    data_0212ceb0[e->type].unk_08 = 0x1af;
}

void dead_move(Entity *e) {
    if (data_0212ceb0[e->type].stateTimer != 0) {
        if (!(e->frame & 0x80)) {
            do {
                UpdateAnimationSingleFrame(e);
            } while (!(e->frame & 0x80));
        }
        func_02085934(e, e->unk_1b);
        data_0212ceb0[e->type].stateTimer = 0;
        return;
    }
    if (e->frame & 0x80) {
        return;
    }
    func_02085934(e, e->unk_1b);
}

void link_jitabata(Entity *e) {
    link_jitabataSubActions[e->subAction](e);
}

void jitabata_init(Entity *e) {
    e->subAction++;
    data_0212ceb0[e->type].unk_08 = 0x250;
}

void link_setMode(Entity *e) {
    func_02085934(e, e->unk_1b);
}

void link_walkback(Entity *e) {
    link_walkbackSubActions[e->subAction](e);
}

void walkback_init(Entity *e) {
    e->subAction++;
    e->direction = ((e->animationState + 4) & 7) << 2;
    e->speed = 0x80;
    data_0212ceb0[e->type].unk_08 = 4;
}

void walkback_move(Entity *e) {
    MoveDir(e);
    func_02085934(e, e->unk_1b);
    e->timer--;
    if (e->timer == 0) {
        data_0212ceb0[e->type].state = 2;
    }
}

void link_buttobi(Entity *e) {
    link_buttobiSubActions[e->subAction](e);
}

void buttobi_init(Entity *e) {
    e->subAction++;
    data_0212ceb0[e->type].unk_08 = 0xae;
    e->direction = 9;
    e->speed = 0x400;
}

void buttobi_kurukuru(Entity *e) {
    MoveDir(e);
    func_02085934(e, e->unk_1b);
    e->speed -= 0x14;
    if (e->x.HALF.HI <= 0xb8) {
        return;
    }
    e->x.HALF.HI = 0xb8;
    e->subAction++;
    data_0212ceb0[e->type].unk_08 = 0x1af;
    e->animationState = 2;
    SoundReq(0x1fc);
}

void buttobi_batari(Entity *e) {
    if (e->frame & 0x80) {
        return;
    }
    func_02085934(e, e->unk_1b);
}

void link_standup(Entity *e) {
    link_standupSubActions[e->subAction](e);
}

void standup_init(Entity *e) {
    e->subAction++;
    e->zVelocity = 0x20000;
    data_0212ceb0[e->type].unk_08 = 0xc;
    SoundReq(0xd);
}

void standup_move_072c24(Entity *e) {
    func_02085934(e, e->unk_1b);
    if (UpdateGravity(e, 0x4000) != 0) {
        return;
    }
    SoundReq(0xe);
    data_0212ceb0[e->type].state = 2;
}
