#include "engine/functions.h"
#include "object/tama06.h"

// Tama06 family, address -> name (original names from symbols.txt):
//   0x0207ead4 Tama06, 0x0207eba0 tama06_type0, 0x0207ebbc tama06_init, 0x0207ecfc tama06_move, 0x0207ed7c tama06_attackInit, 0x0207ee74 tama06_attack, 0x0207ef0c tama06_attackWait, 0x0207ef50 tama06_attackEnd, 0x0207f010 tama06_rlittle, 0x0207f088 tama06_wait
//   (tama06_rlarge 0x0207f0cc is parked in scratch/agentC/nonmatching)

// Tama06, 0x0207ead4. Removes the actor when its parent is dead; otherwise runs the state of its type, copies the
// parent's layer and sprite priority bits, and sets the sprite flag depending on the child and the frame counter.
ARM void Tama06(Entity *e) {
    if (e->parent->health != 0) {
        data_020dce2c[e->type](e);
        e->spriteSettings.b30 = e->parent->spriteSettings.b30;
        e->spriteSettings.b14 = 1;
        e->layer = e->parent->layer;
        if (e->type == 0) {
            return;
        }
        if (e->child->action != 7 && frameCounter % 3 + 1 == e->type) {
            e->spriteSettings.b0 = 1;
        } else {
            e->spriteSettings.b0 = 0;
        }
    } else {
        PutObjWork(e);
    }
}

// tama06_type0, 0x0207eba0. Runs the action of the current state.
ARM void tama06_type0(Entity *e) {
    data_020dce94[e->action](e);
}

// tama06_init, 0x0207ebbc. Makes the three pieces (kinds 1 to 3) as objects linked to this actor and registers them.
ARM void tama06_init(Entity *e) {
    Entity *piece1;
    Entity *piece2;
    Entity *piece3;
    piece1 = GetObjWork();
    if (piece1 == 0) {
        return;
    }
    piece2 = GetObjWork2(piece1);
    if (piece2 == 0) {
        return;
    }
    piece3 = GetObjWork2(piece2);
    if (piece3 == 0) {
        return;
    }
    piece1->objKind = 4;
    piece2->objKind = 4;
    piece3->objKind = 4;
    piece1->objId = 6;
    piece2->objId = 6;
    piece3->objId = 6;
    piece1->type = 1;
    piece2->type = 2;
    piece3->type = 3;
    piece1->parent = e->parent;
    piece2->parent = e->parent;
    piece3->parent = e->parent;
    piece1->child = e;
    piece2->child = e;
    piece3->child = e;
    VARS(Vars_Tama06Piece, piece2)->linkedPiece = piece1;
    VARS(Vars_Tama06Piece, piece3)->linkedPiece = piece1;
    ObjPosCopy(e, piece1);
    ObjPosCopy(e, piece2);
    ObjPosCopy(e, piece3);
    RegistObjWork(5, piece1);
    RegistObjWork(5, piece2);
    RegistObjWork(5, piece3);
    e->action = 1;
    e->unk_2e = 8;
    e->z.HALF.HI = 8 - 12;
    e->spriteSettings.b0 = 1;
    e->hitbox = data_020dce1c;
    e->unk_5e.b0 = 3;
    e->statusFlags = e->statusFlags | 0x80;
    func_0208ae78(e);
    InitAnimationForceUpdate(e, 0);
}

// tama06_move, 0x0207ecfc. While the parent's subtimer is odd and the direction matches the parent's animation it
// turns the piece toward the parent's position with speed 0x700; otherwise it only steps the direction back.
ARM void tama06_move(Entity *e) {
    Entity *parent;
    parent = e->parent;
    if ((parent->subtimer & 1) != 0 && ((parent->animationState - 1) & 3) << 3 == e->direction) {
        e->action = 2;
        e->direction = (e->direction - 8) & 0x1f;
        e->speed = 0x700;
        VARS(Vars_Tama06Move, e)->targetX = parent->x.HALF.HI;
        VARS(Vars_Tama06Move, e)->targetY = parent->y.HALF.HI;
        type0PosSet(e);
        return;
    }
    type0PosSet(e);
    e->direction = (e->direction - 1) & 0x1f;
}

// tama06_attackInit, 0x0207ed7c. Starts the attack: aims at the spot in front of the parent (a table offset from its
// position) and dashes when the direction to the parent matches its animation; the parent's subtimer gets bit 1.
ARM void tama06_attackInit(Entity *e) {
    s16 targetX;
    s16 targetY;
    type0AttackPosSet(e);
    {
        Entity *parent = e->parent;
        const s8 *offset = data_020dce24 + parent->animationState * 2;
        targetX = parent->x.HALF.HI + offset[0];
        targetY = parent->y.HALF.HI + offset[1];
    }
    func_02086200(e, CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, targetX, targetY));
    func_02086200(e, CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, targetX, targetY));
    MoveDir(e);
    if (CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, e->parent->x.HALF.HI, e->parent->y.HALF.HI) != e->parent->animationState << 3) {
        return;
    }
    e->action = 3;
    e->speed = 0x700;
    e->direction = ((e->parent->animationState << 3) + 8) & 0x18;
    e->parent->subtimer = e->parent->subtimer | 2;
    EnqueueSFX(0x61);
}

// tama06_attack, 0x0207ee74. Aims the piece at the parent's direction and slows it down; when the speed drops below
// 0x440 it changes to action 4 with a timer of 0x18.
ARM void tama06_attack(Entity *e) {
    type0AttackPosSet(e);
    func_02086200(e, (u8)(e->parent->animationState << 3));
    func_02086200(e, (u8)(e->parent->animationState << 3));
    func_02086200(e, (u8)(e->parent->animationState << 3));
    func_02086200(e, (u8)(e->parent->animationState << 3));
    MoveDir(e);
    e->speed = e->speed - 0x24;
    if (e->speed < 0x440) {
        e->action = 4;
        e->timer = 0x18;
    }
}

// tama06_attackWait, 0x0207ef0c. Counts the timer down; at zero it changes to action 5 with speed 0x400 and sets bit 1
// of the parent's subtimer.
ARM void tama06_attackWait(Entity *e) {
    type0AttackPosSet(e);
    e->timer = e->timer - 1;
    if (e->timer != 0) {
        return;
    }
    e->action = 5;
    e->speed = 0x400;
    e->parent->subtimer = e->parent->subtimer | 2;
}

// tama06_attackEnd, 0x0207ef50. Speeds the piece up to 0x800 and steers it back to the parent's animation direction.
// When it is within 8 pixels of its old position it changes to action 6 and sets bit 7 of the parent's subtimer;
// otherwise it turns toward the position it moved to and keeps moving.
ARM void tama06_attackEnd(Entity *e) {
    u16 oldX;
    u16 oldY;
    if (e->speed < 0x800) {
        e->speed = e->speed + 0x20;
    }
    oldX = e->x.HALF.HI;
    oldY = e->y.HALF.HI;
    e->direction = ((e->parent->animationState << 3) - 8) & 0x18;
    type0PosSet(e);
    if ((u16)(e->x.HALF.HI - oldX + 8) <= 0x10) {
        e->x.HALF.HI = oldX;
        e->y.HALF.HI = oldY;
        e->action = 6;
        e->timer = 0x20;
        e->parent->subtimer = e->parent->subtimer | 0x80;
        return;
    }
    e->direction = CalculateDirectionTo((s16)oldX, (s16)oldY, e->x.HALF.HI, e->y.HALF.HI);
    e->x.HALF.HI = oldX;
    e->y.HALF.HI = oldY;
    MoveDir(e);
}

// tama06_rlittle, 0x0207f010. Turns the piece by a step of the timer, counts the timer down and, when it is nearly out,
// waits in action 7 with the sound 0x30.
ARM void tama06_rlittle(Entity *e) {
    u8 timer;
    type0PosSetR(e, e->timer >> 1);
    e->direction = (e->direction - 1) & 0x1f;
    e->timer = e->timer - 1;
    timer = e->timer;
    if (timer >= 8) {
        return;
    }
    e->action = 7;
    e->timer = 0x96;
    e->unk_2e = 0;
    e->statusFlags = e->statusFlags & 0x7f;
    type0WaitPosSet(e);
    EnqueueSFX(0x30);
}

// tama06_wait, 0x0207f088. Counts the timer down; at zero it changes to action 8 and sets bit 7 of the flags.
ARM void tama06_wait(Entity *e) {
    type0WaitPosSet(e);
    e->timer = e->timer - 1;
    if (e->timer != 0) {
        return;
    }
    e->action = 8;
    e->timer = 4;
    e->unk_2e = 8;
    e->statusFlags = e->statusFlags | 0x80;
}
