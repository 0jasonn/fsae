#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

typedef struct Vars_PathMover {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ const u16 *pathCursor; // current path command
    /* 74 */ const u16 *pathStart; // path start
    /* 78 */ u16 targetX; // target x
    /* 7a */ u16 targetY; // target y
    /* 7c */ s16 startX; // start x
    /* 7e */ s16 startY; // start y
} Vars_PathMover;
#define V(e) VARS(Vars_PathMover, e)

typedef struct UnkStruct_0212c540 {
    u16 unk_0;
    u16 unk_2;
} UnkStruct_0212c540;
extern UnkStruct_0212c540 data_0212c540;
extern const EntityFunc em2b_actions[];
extern const EntityFunc em2b_moveActions[];
extern const u8 em2b_hitbox[];


ARM void Em2b(Entity *e) {
    if (data_0212c540.unk_2 > 1) {
        func_02084700(e);
    }
    em2b_actions[e->action](e);
}

ARM void em2b_init(Entity *e) {
    e->subtimer = Random();
    e->unk_2e = 6;
    e->hitbox = em2b_hitbox;
    V(e)->startX = e->x.HALF.HI;
    V(e)->startY = e->y.HALF.HI;
    V(e)->pathStart = V(e)->pathCursor = (const u16 *)GetInfoAdrs(e->unk_52, e->type2);
    em2b_getNextInfo(e);
    InitAnimationForceUpdate(e, 0);
    e->action = 1;
    e->spriteSettings.b0 = 1;
}

ARM void em2b_move(Entity *e) {
    em2b_moveActions[e->subAction](e);
}

ARM void em2b_move_u(Entity *e) {
    MoveDir(e);
    if (V(e)->targetY < e->y.HALF.HI) {
        return;
    }
    e->y.HALF.HI = V(e)->targetY;
    em2b_getNextInfo(e);
}

ARM void em2b_move_ur(Entity *e) {
    MoveDir(e);
    if (V(e)->targetY < e->y.HALF.HI) {
        return;
    }
    if (V(e)->targetX > e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = V(e)->targetX;
    e->y.HALF.HI = V(e)->targetY;
    em2b_getNextInfo(e);
}

ARM void em2b_move_r(Entity *e) {
    MoveDir(e);
    if (V(e)->targetX > e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = V(e)->targetX;
    em2b_getNextInfo(e);
}

ARM void em2b_move_dr(Entity *e) {
    MoveDir(e);
    if (V(e)->targetY > e->y.HALF.HI || V(e)->targetX > e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = V(e)->targetX;
    e->y.HALF.HI = V(e)->targetY;
    em2b_getNextInfo(e);
}

ARM void em2b_move_d(Entity *e) {
    MoveDir(e);
    if (V(e)->targetY > e->y.HALF.HI) {
        return;
    }
    e->y.HALF.HI = V(e)->targetY;
    em2b_getNextInfo(e);
}

ARM void em2b_move_dl(Entity *e) {
    MoveDir(e);
    if (V(e)->targetY > e->y.HALF.HI) {
        return;
    }
    if (V(e)->targetX < e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = V(e)->targetX;
    e->y.HALF.HI = V(e)->targetY;
    em2b_getNextInfo(e);
}

ARM void em2b_move_l(Entity *e) {
    MoveDir(e);
    if (V(e)->targetX < e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = V(e)->targetX;
    em2b_getNextInfo(e);
}

ARM void em2b_move_ul(Entity *e) {
    MoveDir(e);
    if (V(e)->targetY < e->y.HALF.HI || V(e)->targetX < e->x.HALF.HI) {
        return;
    }
    e->x.HALF.HI = V(e)->targetX;
    e->y.HALF.HI = V(e)->targetY;
    em2b_getNextInfo(e);
}

ARM void em2b_move_wait(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    em2b_getNextInfo(e);
}

ARM void em2b_getNextInfo(Entity *e) {
    if (V(e)->pathCursor[0] == 0xffff) {
        V(e)->pathCursor = V(e)->pathStart;
    }
    const u16 *cmd = V(e)->pathCursor;
    u16 opcode = cmd[0];
    if (opcode & 0x8000) {
        e->subAction = 8;
        e->timer = cmd[1];
    } else {
        e->direction = opcode;
        e->subAction = (opcode & 0xff) >> 2;
        switch (e->subAction) {
            case 1:
                V(e)->targetX = e->x.HALF.HI + cmd[1];
            case 0:
                V(e)->targetY = e->y.HALF.HI - cmd[1];
                break;
            case 3:
                V(e)->targetY = e->y.HALF.HI + cmd[1];
            case 2:
                V(e)->targetX = e->x.HALF.HI + cmd[1];
                break;
            case 5:
                V(e)->targetX = e->x.HALF.HI - cmd[1];
            case 4:
                V(e)->targetY = e->y.HALF.HI + cmd[1];
                break;
            case 7:
                V(e)->targetY = e->y.HALF.HI - cmd[1];
            case 6:
                V(e)->targetX = e->x.HALF.HI - cmd[1];
                break;
        }
        if (cmd[2] != 0) {
            e->speed = cmd[2];
        }
    }
    V(e)->pathCursor += 4;
}
